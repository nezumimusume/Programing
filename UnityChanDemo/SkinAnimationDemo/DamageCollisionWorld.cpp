/*!
 * @brief	敵、プレイヤーにダメージを与えるコリジョンワールド。
 */

#include "stdafx.h"
#include "DamageCollisionWorld.h"

namespace {
	struct MyContactResultCallback : public btCollisionWorld::ContactResultCallback
	{
		MyContactResultCallback() :
			queryCollisionObject(nullptr),
			hitObject(nullptr)
		{

		}
		btCollisionObject* queryCollisionObject;
		DamageCollisionWorld:: Collision* hitObject;
		float distSq = FLT_MAX;
		virtual	btScalar	addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1) override
		{
			const CVector3* vColl0Pos = (CVector3*)(&colObj0Wrap->getWorldTransform().getOrigin());
			const CVector3* vColl1Pos = (CVector3*)(&colObj1Wrap->getWorldTransform().getOrigin());
			CVector3 vDist;
			vDist.Subtract(*vColl0Pos, *vColl1Pos);
			float distTmpSq = vDist.LengthSq();
			if (distTmpSq < distSq) {
				//こちらの方が近い。
				if (queryCollisionObject == colObj0Wrap->getCollisionObject()) {
					hitObject = (DamageCollisionWorld::Collision*)colObj1Wrap->getCollisionObject()->getUserPointer();
				}
				else {
					hitObject = (DamageCollisionWorld::Collision*)colObj0Wrap->getCollisionObject()->getUserPointer();
				}
				distSq = distTmpSq;
			}
			
			return 0.0f;
		}
	};
}
DamageCollisionWorld::DamageCollisionWorld()
{
}

DamageCollisionWorld::~DamageCollisionWorld()
{
}
void DamageCollisionWorld::Start()
{
	collisionConfig.reset( new btDefaultCollisionConfiguration );
	collisionDispatcher.reset( new btCollisionDispatcher(collisionConfig.get()) );
	overlappingPairCache.reset(new btDbvtBroadphase() );
	collisionWorld.reset(new btCollisionWorld(collisionDispatcher.get(), overlappingPairCache.get(), collisionConfig.get()));
}
/*!
*@brief	ダメージコリジョンと重なっているか調べる。
*/
const DamageCollisionWorld::Collision* DamageCollisionWorld::FindOverlappedDamageCollision(EnAttr attr, const CVector3& pos, float radius) const
{
	for (auto& collision : collisions) {
		if (collision->attr == attr) {
			float t = collision->radius + radius;
			CVector3 diff;
			diff.Subtract(collision->position, pos);
			if (diff.LengthSq() < t * t) {
				//当たった。
				return collision.get();
			}
		}
	}
	return nullptr;
}
const DamageCollisionWorld::Collision* DamageCollisionWorld::FindOverlappedDamageCollision(EnAttr attr, btCollisionObject* colliObject) const
{
	MyContactResultCallback callback;
	callback.queryCollisionObject = colliObject;
	collisionWorld->contactTest(colliObject, callback);

	return callback.hitObject;
}
void DamageCollisionWorld::Update()
{
	std::list<CollisionPtr>::iterator it = collisions.begin();
	while(it != collisions.end()){
		(*it)->time += GameTime().GetFrameDeltaTime();
		if((*it)->time > (*it)->life){
			//死亡。
			collisionWorld->removeCollisionObject((*it)->collisionObject.get());
			it = collisions.erase(it);
		}else{
			it++;
		}
	}
	collisionWorld->updateAabbs();
}
/*!
*@brief	描画
*/
void DamageCollisionWorld::Render(CRenderContext& renderContext) 
{
#ifdef DEBUG_DMG_COLLISION_DRAW
	for (CollisionPtr coll : collisions) {
		CMatrix mWVP;
		mWVP.MakeTranslation(coll->position);
		mWVP.Mul(mWVP, g_camera->GetCamera().GetViewProjectionMatrix());
		coll->debugShape.RenderLightWVP(renderContext, mWVP);
	}
#endif
}