/*!
 * @brief	ディザリング。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/postEffect/tkDithering.h"
#include "tkEngine/graphics/tkPresetRenderState.h"


namespace tkEngine{
	CDithering::CDithering()
	{
	}
	CDithering::~CDithering()
	{
	}
	void CDithering::Release()
	{
	}
	void CDithering::Init(const SGraphicsConfig& config)
	{
		Release();
		m_isEnable = config.ditheringConfig.isEnable;
		m_vsShader.Load("shader/dithering.fx", "VSMain", CShader::EnType::VS);
		m_psShader.Load("shader/dithering.fx", "PSMain", CShader::EnType::PS);
		//サンプラを作成。
		D3D11_SAMPLER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.Filter = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
		m_samplerState.Create(desc);
	}
	void CDithering::Render(CRenderContext& rc)
	{
		if (!m_isEnable) {
			return;
		}
		BeginGPUEvent(L"enRenderStep_Dithering");

		//レンダリングステートをFXAA用に設定するようにする。
		rc.OMSetDepthStencilState(DepthStencilState::disable, 0);
		//現在のレンダリングターゲットを取得。
		CRenderTarget& rt = Engine().GetGraphicsEngine().GetMainRenderTarget();
		//レンダリングターゲットを切り替える。
		Engine().GetGraphicsEngine().ToggleMainRenderTarget();
		CRenderTarget* renderTargets[] = {
			&Engine().GetGraphicsEngine().GetMainRenderTarget()
		};
		rc.PSSetSampler(0, m_samplerState);
		rc.OMSetRenderTargets(1, renderTargets);
		rc.PSSetShaderResource(0, rt.GetRenderTargetSRV());
		rc.PSSetShader(m_psShader);
		rc.VSSetShader(m_vsShader);
		//入力レイアウトを設定。
		rc.IASetInputLayout(m_vsShader.GetInputLayout());

		GraphicsEngine().GetPostEffect().DrawFullScreenQuad(rc);
		rc.OMSetDepthStencilState(DepthStencilState::SceneRender, 0);
		EndGPUEvent();

		EndGPUEvent();
	}
}