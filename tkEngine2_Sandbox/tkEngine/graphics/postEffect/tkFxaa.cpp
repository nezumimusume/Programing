/*!
 *@brief	FXAA
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/postEffect/tkFxaa.h"

namespace tkEngine{
	CFxaa::CFxaa()
	{
	}
	CFxaa::~CFxaa()
	{
		Release();
	}
	void CFxaa::Release()
	{
	}
	void CFxaa::Init(const SGraphicsConfig& config)
	{
		Release();
		m_isEnable = config.aaConfig.isEnable;
		m_vsShader.Load("Assets/shader/fxaa.fx", "VSMain", CShader::EnType::VS);
		m_psShader.Load("Assets/shader/fxaa.fx", "PSMain", CShader::EnType::PS);
	}
	void CFxaa::Render(CRenderContext& rc)
	{
		if (!m_isEnable) {
			return;
		}
		BeginGPUEvent(L"enRenderStep_AntiAlias");
		//@todo レンダリングステートをFXAA用に設定するようにする。
		
		//現在のレンダリングターゲットを取得。
		CRenderTarget& rt = Engine().GetGraphicsEngine().GetMainRenderTarget();
		//レンダリングターゲットを切り替える。
		Engine().GetGraphicsEngine().ToggleMainRenderTarget();
		CRenderTarget* renderTargets[] = {
			&Engine().GetGraphicsEngine().GetMainRenderTarget()
		};
		rc.OMSetRenderTargets(1, renderTargets);
		rc.PSSetShaderResource(0, rt.GetRenderTargetSRV());
		rc.PSSetShader(m_psShader);
		rc.VSSetShader(m_vsShader);
		//入力レイアウトを設定。
		rc.IASetInputLayout(m_vsShader.GetInputLayout());

		GraphicsEngine().GetPostEffect().DrawFullScreenQuad(rc);
		
		EndGPUEvent();
	}
}
