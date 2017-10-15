#pragma once

#include "tkEngine/Physics/tkCollisionAttr.h"

namespace tkEngine{
	class CRigidBody;

	class CPhysicsWorld
	{
		btDefaultCollisionConfiguration*		collisionConfig = nullptr;
		btCollisionDispatcher*					collisionDispatcher = nullptr;	//!<�Փˉ��������B
		btBroadphaseInterface*					overlappingPairCache = nullptr;	//!<�u���[�h�t�F�[�Y�B�Փ˔���̎}�؂�B
		btSequentialImpulseConstraintSolver*	constraintSolver = nullptr;		//!<�R���X�g���C���g�\���o�[�B�S�������̉��������B
		btDiscreteDynamicsWorld*				dynamicWorld = nullptr;			//!<���[���h�B
	public:
		CPhysicsWorld();
		~CPhysicsWorld();
		void Init();
		void Update() ;
		void Release();
		/*!
		* @brief	�_�C�i�~�b�N���[���h���擾�B
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