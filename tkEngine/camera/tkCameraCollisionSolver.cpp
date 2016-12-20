/*!
 *@brief	カメラのコリジョンソルバー。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/camera/tkCameraCollisionSolver.h"

namespace tkEngine{
	struct SConvexSweepCallback : public btCollisionWorld::ClosestConvexResultCallback
	{
	public:
		CVector3 m_rayDir;
		SConvexSweepCallback(CVector3 rayDir) :
			btCollisionWorld::ClosestConvexResultCallback(btVector3(0.0f, 0.0f, 0.0f), btVector3(0.0f, 0.0f, 0.0f) ),
			m_rayDir(rayDir){}
		virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
		{
			CVector3 normal;
			normal.Set(convexResult.m_hitNormalLocal);
			if (normal.Dot(m_rayDir) > 0.0f) {
				return 1.0f;
			}
			if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Character) {
				return 1.0f;
			}
			return btCollisionWorld::ClosestConvexResultCallback::addSingleResult(convexResult, normalInWorldSpace);
		}
	};
	CCameraCollisionSolver::CCameraCollisionSolver()
	{
	}
	CCameraCollisionSolver::~CCameraCollisionSolver()
	{
	}
	void CCameraCollisionSolver::Init(float radius)
	{
		m_radius = radius;
		m_collider.Create(radius);
	}
	bool CCameraCollisionSolver::Execute( CCamera& camera )
	{
		CVector3 target = camera.GetTarget();
		CVector3 position = camera.GetPosition();
		CVector3 vWk;
		vWk.Subtract(target, position);
		if (vWk.LengthSq() < FLT_EPSILON) {
			//視点と注視点がほぼ同じ座標にある。
			return false;
		}
		vWk.Normalize();
		//レイを作成する。
		btTransform btStart, btEnd;
		btStart.setIdentity();
		btEnd.setIdentity();
		btStart.setOrigin(btVector3(target.x, target.y, target.z));
		btEnd.setOrigin(btVector3(position.x, position.y, position.z));
		SConvexSweepCallback callback(vWk);
	//	callback.m_collisionFilterGroup = 
		PhysicsWorld().ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), btStart, btEnd, callback);
		if (callback.hasHit()) {
			CVector3 vHitPointNormal;
			vHitPointNormal.Set(callback.m_hitNormalWorld);
			vWk.Set(callback.m_hitPointWorld);
			vWk.Subtract(vWk, position);
			float t = vWk.Dot(vHitPointNormal);
			CVector3 vOffset;
			vOffset = vHitPointNormal;
			vOffset.Scale(t+m_radius*0.8f);

			//視点を衝突点にしてみるテスト。
			position.Add(vOffset);

			camera.SetPosition(position);
			return true;
		}
		return false;
	}
}
