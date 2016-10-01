/*!
 * @brief	�L�����N�^�̃R���W�����R���g���[���B
 */

#include "stdafx.h"
#include "CharacterCollisionController.h"

namespace{
	//�n�ʂƂ̓����蔻��B
	struct SweepResultGround : public btCollisionWorld::ConvexResultCallback
	{
		bool isHit;
		CVector3 hitPos;
		CVector3 startPos;
		float dist;
		CVector3 hitNormal;
		SweepResultGround()
		{
			isHit = false;
			dist = FLT_MAX;
			hitPos = CVector3::Zero;
			startPos = CVector3::Zero;
			hitNormal = CVector3::Zero;
		}

		virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
		{
			CVector3 hitNormalTmp = *(CVector3*)&convexResult.m_hitNormalLocal;
			float t = fabsf(acosf(hitNormalTmp.Dot(CVector3::Up)));
			if (t < CMath::PI * 0.3f) {
				isHit = true;
				CVector3 hitPosTmp = *(CVector3*)&convexResult.m_hitPointLocal;
				//��_�Ƃ̋����𒲂ׂ�B
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
	//��
	struct SweepResultWall : public btCollisionWorld::ConvexResultCallback
	{
		bool isHit;
		CVector3 hitPos;
		CVector3 startPos;
		float dist;
		CVector3 hitNormal;
		SweepResultWall()
		{
			isHit = false;
			dist = FLT_MAX;
			hitPos = CVector3::Zero;
			startPos = CVector3::Zero;
			hitNormal = CVector3::Zero;
		}

		virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
		{
			CVector3 hitNormalTmp = *(CVector3*)&convexResult.m_hitNormalLocal;
			float t = fabsf(acosf(hitNormalTmp.Dot(CVector3::Up)));
			if (t >= CMath::PI * 0.3f) {
				isHit = true;
				CVector3 hitPosTmp = *(CVector3*)&convexResult.m_hitPointLocal;
				//��_�Ƃ̋����𒲂ׂ�B
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

CharacterCollisionController::CharacterCollisionController()
{
}
CharacterCollisionController::~CharacterCollisionController()
{
}

/*!
 * @brief	���s�B
 */
void CharacterCollisionController::Execute( CVector3& position, const CVector3& nextPosition )
{
	//XZ���ʂ𒲂ׂ�B
	{
		int loopCount = 0;
		while (true) {
			CVector3 addPos;
			addPos.Subtract(nextPosition, position);
			CVector3 posTmp = position;
			posTmp.y += radius + 0.2f;
			btTransform start, end;
			start.setIdentity();
			end.setIdentity();
			start.setOrigin(*(btVector3*)(&posTmp));
			CVector3 newPos;
			SweepResultWall callback;
			callback.startPos = position;
			CVector3 addPosXZ = addPos;
			addPosXZ.y = 0.0f;
			if (addPosXZ.Length() > 0.0001f) {
				newPos.Add(posTmp, addPosXZ);
				end.setOrigin(btVector3(newPos.x, newPos.y, newPos.z));

				g_physicsWorld->ConvexSweepTest((const btConvexShape*)collider.GetBody(), start, end, callback);
			}
			if (callback.isHit) {
				//���������B
				float t = fabsf(acosf(callback.hitNormal.Dot(CVector3::Up)));
				if (t >= CMath::PI * 0.3f) {
					//�ǁB
					nextPosition.x = callback.hitPos.x;
					nextPosition.z = callback.hitPos.z;
					//���a�������߂��B
					CVector3 hitNormalXZ = callback.hitNormal;
					hitNormalXZ.y = 0.0f;
					hitNormalXZ.Normalize();
					CVector3 t = hitNormalXZ;
					t.Scale(radius);
					nextPosition.Add(t);
					//�����ĕǂɉ����Ċ��点��B
					t.Cross(hitNormalXZ, CVector3::Up);
					t.Normalize();
					//�����߂��œ��������͌��Z����B
					CVector3 t2;
					t2.Subtract(nextPosition, position);
					t2.y = 0.0f;
					addPosXZ.Subtract(t2);
					t.Scale(t.Dot(addPosXZ));
					nextPosition.Add(t);
				}
			}
			else {
				//�ǂ��Ƃ�������Ȃ��̂ŏI���B
				break;
			}
			loopCount++;
			if (loopCount == 5) {
				break;
			}
		}
	}
	//�������𒲂ׂ�B
	{
		CVector3 addPos;
		addPos.Subtract(nextPosition, position);
		btTransform start, end;
		start.setIdentity();
		end.setIdentity();
		start.setOrigin(btVector3(position.x, position.y + radius, position.z));
		CVector3 newPos;
		SweepResultGround callback;
		callback.startPos = position;
		if (addPos.y < 0.0f) {
			newPos = (*(CVector3*)&start.getOrigin());
			newPos.y += addPos.y;

			end.setOrigin(btVector3(newPos.x, newPos.y, newPos.z));

			g_physicsWorld->ConvexSweepTest((const btConvexShape*)collider.GetBody(), start, end, callback);
		}
		if (callback.isHit) {
			//���������B
			float t = fabsf(acosf(callback.hitNormal.Dot(CVector3::Up)));
			if (t < CMath::PI * 0.3f) {
				//�n�ʁB
				CVector3 Circle;
				float x = 0.0f;
				float offset = 0.0f;	//�����߂��ʁB
				Circle = CVector3::Zero;

				Circle = position;
				Circle.y = callback.hitPos.y;//�~�̒��S
				CVector3 v;
				v.Subtract(Circle, callback.hitPos);
				x = v.Length();//���̂̊p�ƃv���C���[�̊Ԃ̉����̋��������܂�B

				offset = sqrt(max(0.0f, radius*radius - x*x));//y�̕����������߂�B

				moveSpeed.y = 0.0f;
				isJump = false;
				nextPosition.y = callback.hitPos.y + offset - radius;
			}
		}
	}
	position = nextPosition;
}