/*!
 *@brief	ZPrepass
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/preRender/tkZPrepass.h"
#include "tkEngine/graphics/tkCamera.h"

namespace tkEngine{
	namespace {
		static const int RESERVE_SKIN_MODEL_LIST = 512;
	}
	CZPrepass::CZPrepass()
	{
		m_skinModels.reserve(RESERVE_SKIN_MODEL_LIST);
	}
	CZPrepass::~CZPrepass()
	{
	}
	void CZPrepass::Init()
	{
		//�[�x�l�������ݗp�̃����_�����O�^�[�Q�b�g�̍쐬�B
		DXGI_SAMPLE_DESC multiSampleDesc;
		multiSampleDesc.Count = 1;
		multiSampleDesc.Quality = 0;
		m_depthBuffer.Create(
			GraphicsEngine().GetFrameBufferWidth(),
			GraphicsEngine().GetFrameBufferHeight(),
			1,
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_D24_UNORM_S8_UINT,
			multiSampleDesc
		);
	}
	void CZPrepass::Render(CRenderContext& rc) 
	{
		//���݂̃����_�����O�^�[�Q�b�g���o�b�N�A�b�v����B
		CRenderTarget* oldRenderTargets[MRT_MAX];
		unsigned int numRenderTargetViews;
		rc.OMGetRenderTargets(numRenderTargetViews, oldRenderTargets);
		//�����_�����O�^�[�Q�b�g��ύX����B
		CRenderTarget* renderTargets[] = {
			&m_depthBuffer
		};
		rc.OMSetRenderTargets(1, renderTargets);
		float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //red,green,blue,alpha
		rc.ClearRenderTargetView(0, ClearColor);

		for (auto skinModel : m_skinModels) {
			skinModel->Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix(), true);
		}
		m_skinModels.clear();
		//�����_�����O�^�[�Q�b�g�������߂��B
		rc.OMSetRenderTargets(numRenderTargetViews, oldRenderTargets);
	}
}