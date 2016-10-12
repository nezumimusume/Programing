/*!
 * @brief	敵、プレイヤーにダメージを与えるコリジョンワールド。
 */

#include "stdafx.h"
#include "DamageCollisionWorld.h"

DamageCollisionWorld::DamageCollisionWorld()
{
}

DamageCollisionWorld::~DamageCollisionWorld()
{
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
void DamageCollisionWorld::Update()
{
	std::list<CollisionPtr>::iterator it = collisions.begin();
	while(it != collisions.end()){
		(*it)->time += GameTime().GetFrameDeltaTime();
		if((*it)->time > (*it)->life){
			//死亡。
			it = collisions.erase(it);
		}else{
			it++;
		}
	}
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