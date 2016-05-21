#include "stdafx.h"
#include "DebriCreator.h"
#include "Debri.h"
#include "Camera.h"
#include "bulletPhysics.h"
extern CGameCamera g_gameCamera;

struct SCollisionResult : public btCollisionWorld::ConvexResultCallback
{
	bool isHit;
	CVector3 hitPos;
	CVector3 startPos;
	float dist;
	SCollisionResult()
	{
		isHit = false;
		dist = FLT_MAX;
	}

	virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject->getUserIndex() != -1) {
			//�����B
			return 0.0f;
		}
		//��_�ƃ��C�̎n�_�Ƃ̋����𒲂ׂ�B
		CVector3 vDist;
		vDist.Set(
			convexResult.m_hitPointLocal.x(),
			convexResult.m_hitPointLocal.y(),
			convexResult.m_hitPointLocal.z()
		);
		vDist.Subtract(startPos);
		float distTmp = vDist.LengthSq();
		if (distTmp < dist) {
			//�������̂ق����߂��B
			hitPos.Set(
				convexResult.m_hitPointLocal.x(),
				convexResult.m_hitPointLocal.y(),
				convexResult.m_hitPointLocal.z());
			dist = distTmp;

		}
		
		isHit = true;
		return 0.0f;
	}
};
void CDebriCreator::Start()
{
	m_interval = 0.0f;
	m_sphereColli = new btSphereShape(0.1f);
}
void CDebriCreator::OnDestroy()
{
	delete m_sphereColli;
}

void CDebriCreator::Update()
{
	if (KeyInput().IsMouseLButtonUp()) {
		//���C���΂��ăf�u���𐶐�������W�����߂�B
		CVector4 start;
		CVector4 end;
		
		start.x = (float)KeyInput().GetMousePositionX();
		start.y = (float)KeyInput().GetMousePositionY();
		start.z = 0.0f;
		start.w = 1.0f;
		end.x = (float)KeyInput().GetMousePositionX();
		end.y = (float)KeyInput().GetMousePositionY();
		end.z = 1.0f;
		end.w = 1.0f;

		int screenW = tkEngine::CEngine::Instance().GetFrameBufferWidth();
		int screenH = tkEngine::CEngine::Instance().GetFrameBufferHeight();
		CMatrix mViewInv = m_pCamera->GetViewMatrix();
		CMatrix mProjInv = m_pCamera->GetProjectionMatrix();
#if 1 //DirectX�̊֐����g�p�����o�[�W�����B
		{
			D3DVIEWPORT9 vp;
			Engine().GetD3DDevice()->GetViewport(&vp);
			D3DXVec3Unproject(
				reinterpret_cast<D3DXVECTOR3*>(&start), 
				reinterpret_cast<const D3DXVECTOR3*>(&start),
				&vp,
				reinterpret_cast<const D3DXMATRIX*>(&mProjInv),
				reinterpret_cast<const D3DXMATRIX*>(&mViewInv),
				NULL
				);

			D3DXVec3Unproject(
				reinterpret_cast<D3DXVECTOR3*>(&end),
				reinterpret_cast<const D3DXVECTOR3*>(&end),
				&vp,
				reinterpret_cast<const D3DXMATRIX*>(&mProjInv),
				reinterpret_cast<const D3DXMATRIX*>(&mViewInv),
				NULL
				);
		}
#else
		CMatrix mVpInv = CMatrix::Identity;
		
		//3D��Ԃ̍��W���X�N���[�����W�n�ɕϊ�����ɂ́A�J�����s��~�v���W�F�N�V�����s��~�X�N���[���s�����Z���Ă��΂����E�E�E
		//�܂�A�X�N���[�����W�n����R�c��Ԃ̍��W�ɖ߂����߂ɂ́A�X�N���[���s��̋t�s��~�v���W�F�N�V�����s��̋t�s��~�J�����s��̋t�s���
		//��Z���Ă��΂������ƂɂȂ�B(�t�s�����Z����Ƃ������Ƃ́A���̕ϊ���ł������Ƃ����Ӗ�������B�j

		//�X�N���[�����W�n���琳�K�����W�n�ɕϊ����邽�߂̍s����v�Z����B
		mVpInv.m[0][0] = screenW / 2.0f;
		mVpInv.m[1][1] = -screenH / 2.0f;
		mVpInv.m[3][0] = screenW / 2.0f;
		mVpInv.m[3][1] = screenH / 2.0f;
		mVpInv.Inverse(mVpInv);		//���K�����W�n�ɕϊ����邽�߂ɂ̓X�N���[�����W�n�ɕϊ�����s��̋t�s������߂��炢���B
		//���K�����W�n����J�������W�n�ɕϊ�����s����v�Z����B
		mProjInv.Inverse(mProjInv);	//�J�������W�n�ɕϊ�����ɂ́A�ˉe��Ԃɕϊ�����s��̋t�s������߂�B
		mViewInv.Inverse(mViewInv);	//���[���h���W�n�ɕϊ�����ɂ́A�J�����s��̋t�s������߂�B
		//�X�N���[���s��̋t�s��~�v���W�F�N�V�����s��̋t�s��~�J�����s��̋t�s������߂�B
		CMatrix mInv;
		mInv.Mul(mVpInv, mProjInv);
		mInv.Mul(mInv, mViewInv);
		mInv.Mul(start);
		mInv.Mul(end);
		//�v���W�F�N�V�����s����������w�Ŋ���K�v������̂ŁA���Z����B
		start.x /= start.w;
		start.y /= start.w;
		start.z /= start.w;
		end.x /= end.w;
		end.y /= end.w;
		end.z /= end.w;
#endif
		//������𒲂ׂ�
		btTransform btStart, btEnd;
		btStart.setIdentity();
		btEnd.setIdentity();
		btStart.setOrigin(btVector3(start.x, start.y, start.z));
		btEnd.setOrigin(btVector3(end.x, end.y, end.z));
		SCollisionResult callback;
		callback.startPos.Set(start.x, start.y, start.z);
		g_bulletPhysics.ConvexSweepTest(m_sphereColli, btStart, btEnd, callback);
		if (callback.isHit) {
			CDebri* debri = CGameObjectManager::Instance().NewGameObject<CDebri>(0);
			callback.hitPos.y += 0.05f;
			debri->Build(CVector3(0.02f, 0.02f, 0.02f), callback.hitPos);
			debri->SetCamera(m_pCamera);
		}
	}
}
void CDebriCreator::Render(CRenderContext& renderContext)
{

}