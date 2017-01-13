/*!
 * @brief	モノクロフィルター。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/postEffect/tkMonochromeFilter.h"
#include "tkEngine/graphics/tkEffect.h"

namespace tkEngine{
	CMonochromeFilter::CMonochromeFilter()
	{
		
	}
	CMonochromeFilter::~CMonochromeFilter()
	{
	}
	void CMonochromeFilter::Create(const SGraphicsConfig& config)
	{
		m_effect = EffectManager().LoadEffect("Assets/presetShader/monochromeFilter.fx");
	}
	void CMonochromeFilter::Render( CRenderContext& renderContext, CPostEffect* postEffect )
	{
		if(m_isEnable){
			
			//レンダリングターゲットを切り替え。
			Engine().ToggleMainRenderTarget();
			//Zバッファだけクリアするためのレンダリングターゲットを作成。
			m_clearRenderTarget.SetSurfaceDX(nullptr);
			m_clearRenderTarget.SetDepthSurfaceDX(Engine().GetMainRenderTarget().GetDepthSurfaceDx());
			renderContext.SetRenderTarget(0, &m_clearRenderTarget);
			//Zバッファをクリア。
			renderContext.Clear(0, nullptr, D3DCLEAR_ZBUFFER, 0, 0.0f, 0);
			renderContext.SetRenderState(RS_ZWRITEENABLE, TRUE);
			renderContext.SetRenderState(RS_ZENABLE, TRUE);
			renderContext.SetRenderState(RS_ZFUNC, D3DCMP_GREATEREQUAL);
			//Zマスクをレンダリング。
			for (auto func : maskModelsFunc) {
				(*func)(renderContext);
			}
			maskModelsFunc.clear();

			CPIXPerfTag tag(renderContext, L"CMonochromeFilter::Render");
			float texSize[] = {
				s_cast<float>(Engine().GetMainRenderTarget().GetWidth()),
				s_cast<float>(Engine().GetMainRenderTarget().GetHeight())
			};
			m_effect->SetTechnique(renderContext, "Default");
			m_effect->Begin(renderContext);
			m_effect->BeginPass(renderContext, 0);
			m_effect->SetTexture(renderContext, "g_scene", Engine().GetMainRenderTarget().GetTexture());
			m_effect->SetValue(renderContext, "g_sceneTexSize", texSize, sizeof(texSize));
			m_effect->SetValue(renderContext, "g_blendRate", &m_blendRate, sizeof(m_blendRate));
			m_effect->CommitChanges(renderContext);

			renderContext.SetRenderState(RS_ZFUNC, D3DCMP_EQUAL);
			renderContext.SetRenderTarget(0, &Engine().GetMainRenderTarget());
			postEffect->RenderFullScreen(renderContext);
			renderContext.SetRenderState(RS_ZFUNC, D3DCMP_LESSEQUAL);
			m_effect->EndPass(renderContext);
			m_effect->End(renderContext);
		}
	}
	

}