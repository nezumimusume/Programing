/*!
 * @brief	キャラクタのコリジョンコントロール。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/character/tkCharacterController.h"
#include "tkEngine/character/tkCollisionAttr.h"
namespace tkEngine{

	namespace{
		//地面との当たり判定。
		struct SweepResultGround : public btCollisionWorld::ConvexResultCallback
		{
			bool isHit = false;
			CVector3 hitPos = CVector3(0.0f, -FLT_MAX, 0.0f);
			CVector3 startPos = CVector3::Zero;
			CVector3 hitNormal = CVector3::Zero;
			btCollisionObject* me = nullptr;
			float dist = FLT_MAX;
			SweepResultGround()
			{
			}

			virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
			{
				if (convexResult.m_hitCollisionObject == me) {
					//自分に衝突した。
					return 0.0f;
				}
				CVector3 hitNormalTmp = *(CVector3*)&convexResult.m_hitNormalLocal;
				float t = hitNormalTmp.Dot(CVector3::Up);
				t = fabsf(acosf(t));
				if ((t < CMath::PI * 0.3f
					&& convexResult.m_hitCollisionObject->getUserIndex() != enCollisionAttr_Character)
					|| convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Ground
					) {
					isHit = true;
					CVector3 hitPosTmp = *(CVector3*)&convexResult.m_hitPointLocal;
					//交点の高さを調べる。。
					CVector3 vDist;
					vDist.Subtract(hitPosTmp, startPos);
					float distTmp = vDist.Length();
					if (dist > distTmp) {
						hitPos = hitPosTmp;
						hitNormal = *(CVector3*)&convexResult.m_hitNormalLocal;
						dist = distTmp;
					}
				}
				return 0.0f;
			}
		};
		//壁
		struct SweepResultWall : public btCollisionWorld::ConvexResultCallback
		{
			bool isHit = false;
			CVector3 hitPos = CVector3::Zero;
			CVector3 startPos = CVector3::Zero;
			float dist = FLT_MAX;
			CVector3 hitNormal = CVector3::Zero;
			btCollisionObject* me = nullptr;
			SweepResultWall()
			{
			}
			virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
			{
				if (convexResult.m_hitCollisionObject == me ) {
					//自分に衝突した。or 地面に衝突した。
					return 0.0f;
				}
				CVector3 hitNormalTmp = *(CVector3*)&convexResult.m_hitNormalLocal;
				float t = fabsf(acosf(hitNormalTmp.Dot(CVector3::Up)));
				if (t >= CMath::PI * 0.3f 
					|| convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Character
				) {
					isHit = true;
					CVector3 hitPosTmp = *(CVector3*)&convexResult.m_hitPointLocal;
					//交点との距離を調べる。
					CVector3 vDist;
					vDist.Subtract(hitPosTmp, startPos);
					float distTmp = vDist.Length();
					if (distTmp < dist) {
						hitPos = hitPosTmp;
						dist = distTmp;
						hitNormal = *(CVector3*)&convexResult.m_hitNormalLocal;
					}
				}
				return 0.0f;
			}
		};
	}

	CCharacterController::CCharacterController() :
		moveSpeed(CVector3::Zero),
		position(CVector3::Zero),
		isJump(false),
		radius(0.0f)
	{
	}
	CCharacterController::~CCharacterController()
	{
	}
	void CCharacterController::Init(float radius, float height, const CVector3& position)
	{
		this->position = position;
		//コリジョン作成。
		this->radius = radius;
		this->height = height;
		collider.Create(radius, height);

		//剛体を初期化。
		RigidBodyInfo rbInfo;
		rbInfo.collider = &collider;
		rbInfo.mass = 0.0f;
		rigidBody.Create(rbInfo);
		btTransform& trans = rigidBody.GetBody()->getWorldTransform();
		//剛体の位置を更新。
		trans.setOrigin(btVector3(position.x, position.y, position.z));
		//@todo 未対応。trans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
		rigidBody.GetBody()->setUserIndex(enCollisionAttr_Character);
		rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
		PhysicsWorld().AddRigidBody(&rigidBody);

	}
	void CCharacterController::Execute()
	{
		//Y方向には重力落下を加える。
		const float GRAVITY = -18.8f;
		moveSpeed.y += GRAVITY * GameTime().GetFrameDeltaTime();
		CVector3 nextPosition = position;
		CVector3 addPos = moveSpeed;
		addPos.Scale(GameTime().GetFrameDeltaTime());
		nextPosition.Add(addPos);
			
		//XZ平面を調べる。
		{
			int loopCount = 0;
			while (true) {
				CVector3 addPos;
				addPos.Subtract(nextPosition, position);
				CVector3 posTmp = position;
				posTmp.y += height * 0.5f + radius + 0.2f;
				btTransform start, end;
				start.setIdentity();
				end.setIdentity();
				start.setOrigin(btVector3(posTmp.x, posTmp.y, posTmp.z));
				CVector3 newPos;
				SweepResultWall callback;
				callback.me = rigidBody.GetBody();
				callback.startPos = posTmp;
				CVector3 addPosXZ = addPos;
				addPosXZ.y = 0.0f;
				if (addPosXZ.Length() > 0.0001f) {
					newPos.Add(posTmp, addPosXZ);
					end.setOrigin(btVector3(newPos.x, newPos.y, newPos.z));

					PhysicsWorld().ConvexSweepTest((const btConvexShape*)collider.GetBody(), start, end, callback);
				}
				if (callback.isHit) {
					//当たった。
					//壁。
					CVector3 vT0, vT1;
					//XZ平面上での移動後の座標をvT0に、交点の座標をvT1に設定する。
					vT0.Set(nextPosition.x, 0.0f, nextPosition.z);
					vT1.Set(callback.hitPos.x, 0.0f, callback.hitPos.z);
					//めり込みが発生している移動ベクトルを求める。
					CVector3 vMerikomi;
					vMerikomi.Subtract(vT0, vT1);
					//XZ平面での衝突した壁の法線を求める。。
					CVector3 hitNormalXZ = callback.hitNormal;
					hitNormalXZ.y = 0.0f;
					hitNormalXZ.Normalize();
					//めり込みベクトルを壁の法線に射影する。
					float fT0 = hitNormalXZ.Dot(vMerikomi);
					//押し戻し返すベクトルを求める。
					//押し返すベクトルは壁の法線に射影されためり込みベクトル+半径。
					CVector3 vOffset;
					vOffset = hitNormalXZ;
					vOffset.Scale(-fT0 + radius);
					nextPosition.Add(vOffset);
				}
				else {
					//どことも当たらないので終わり。
					break;
				}
				loopCount++;
				if (loopCount == 5) {
					//移動できない。
					break;
				}
			}
		}
		//XZの移動は確定。
		position.x = nextPosition.x;
		position.z = nextPosition.z;
		//下方向を調べる。
		{
			CVector3 addPos;
			addPos.Subtract(nextPosition, position);
			
			position = nextPosition;	//移動の仮確定。
			btTransform start, end;
			start.setIdentity();
			end.setIdentity();
			start.setOrigin(btVector3(position.x, position.y + height * 0.5f + radius, position.z));
			CVector3 newPos;
			SweepResultGround callback;
			callback.me = rigidBody.GetBody();
			callback.startPos = (*(CVector3*)&start.getOrigin());
			newPos = (*(CVector3*)&start.getOrigin());
			if (addPos.y > 0.0f) {
				//XZに移動した結果めり込んでいる可能性があるので上に移動していても下を調べる。
				newPos.y -= addPos.y * 0.1f;
			}
			else {
				//落下している場合はそのまま下を調べる。
				newPos.y += addPos.y;
			}
			end.setOrigin(btVector3(newPos.x, newPos.y, newPos.z));

			PhysicsWorld().ConvexSweepTest((const btConvexShape*)collider.GetBody(), start, end, callback);

			if (callback.isHit) {
				//当たった。
				CVector3 Circle;
				float x = 0.0f;
				float offset = 0.0f;	//押し戻す量。
				Circle = CVector3::Zero;

				Circle = position;
				Circle.y = callback.hitPos.y;//円の中心
				CVector3 v;
				v.Subtract(Circle, callback.hitPos);
				x = v.Length();//物体の角とプレイヤーの間の横幅の距離が求まる。

				offset = sqrt(max(0.0f, radius*radius - x*x));//yの平方根を求める。

				moveSpeed.y = 0.0f;
				isJump = false;
				nextPosition.y = callback.hitPos.y + offset - radius;
			}
		}
		position = nextPosition;
		btRigidBody* btBody = rigidBody.GetBody();
		//剛体を動かす。
		btBody->setActivationState(DISABLE_DEACTIVATION);
		btTransform& trans = btBody->getWorldTransform();
		//剛体の位置を更新。
		trans.setOrigin(btVector3(position.x, position.y, position.z));
		//@todo 未対応。 trans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
	}
	/*!
	* @brief	死亡したことを通知。
	*/
	void CCharacterController::RemoveRigidBoby()
	{
		PhysicsWorld().RemoveRigidBody(&rigidBody);
	}
}
