#pragma once

namespace tkEngine{
	class CRigidBody;

	class CPhysicsWorld : public IGameObject
	{
		btDefaultCollisionConfiguration*		collisionConfig;
		btCollisionDispatcher*					collisionDispatcher;	//!<衝突解決処理。
		btBroadphaseInterface*					overlappingPairCache;	//!<ブロードフェーズ。衝突判定の枝切り。
		btSequentialImpulseConstraintSolver*	constraintSolver;		//!<コンストレイントソルバー。拘束条件の解決処理。
		btDiscreteDynamicsWorld*				dynamicWorld;			//!<ワールド。
	public:
		CPhysicsWorld();
		~CPhysicsWorld();
		void Start() override;
		void Update() override;
		void Render(tkEngine::CRenderContext& renderContext)override;
		/*!
		* @brief	ダイナミックワールドを取得。
		*/
		btDiscreteDynamicsWorld* GetDynamicWorld()
		{
			return dynamicWorld;
		}
		void AddRigidBody(CRigidBody* rb);
		void RemoveRigidBody(CRigidBody* rb);
		void ConvexSweepTest(
			const btConvexShape* castShape,
			const btTransform& convexFromWorld,
			const btTransform& convexToWorld,
			btCollisionWorld::ConvexResultCallback& resultCallback,
			btScalar allowedCcdPenetration = 0.0f
			)
		{
			dynamicWorld->convexSweepTest(castShape, convexFromWorld, convexToWorld, resultCallback, allowedCcdPenetration);
		}
	};
}
