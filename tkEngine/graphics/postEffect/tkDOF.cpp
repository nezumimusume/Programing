/*!
 * @brief	被写界深度。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/postEffect/tkDOF.h"
#include "tkEngine/graphics/tkEffect.h"

namespace tkEngine{
	/*!
	 * @brief	コンストラクタ。
	 */
	CDof::CDof() :
		m_isEnable(false),
		m_pint(3000.0f),
		m_focalLength(24.0f),
		m_F(5.6f)
	{
	}
	/*!
	 * @brief	デストラクタ。
	 */
	CDof::~CDof()
	{
	}
	
	void CDof::Release()
	{
		m_depthRT.Release();
	}
	
	void CDof::Create(const SGraphicsConfig& config)
	{
		if (config.dofConfig.isEnable) {
			//DOFが有効。
			m_isEnable = config.dofConfig.isEnable;
			//DOFはメインレンダリングターゲットに書き込むときにMRTを使用して書き込むので、
			//メインと同じ幅と高さ。
			int w = Engine().GetFrameBufferWidth();
			int h = Engine().GetFrameBufferHeight();
			//16bit。
			m_depthRT.Create(w, h, 1, D3DFMT_R16F, D3DFMT_UNKNOWN, D3DMULTISAMPLE_NONE, 0);
			
			m_blurForward.Init(w, h, *Engine().GetMainRenderTarget().GetTexture());
			m_blurBack.Init(w, h, *Engine().GetMainRenderTarget().GetTexture());
			m_blurBack.SetBlurPower(2.0f);
			m_blurBack.SetUseWeights(CGaussianBlur::enUseWeight_8);
			m_blurForward.SetBlurPower(20.0f);
			m_blurForward.SetUseWeights(CGaussianBlur::enUseWeight_8);
			m_effect = EffectManager().LoadEffect("Assets/presetShader/dof.fx");

			LPDIRECT3DTEXTURE9 tex = Engine().GetMainRenderTarget().GetTexture()->GetTextureDX();
			D3DSURFACE_DESC desc;
			tex->GetLevelDesc(0, &desc);

			m_combineRenderTarget.Create(
				m_blurBack.GetRenderTarget().GetWidth(),
				m_blurBack.GetRenderTarget().GetHeight(),
				1,
				desc.Format,
				D3DFMT_UNKNOWN,
				D3DMULTISAMPLE_NONE, 
				0
			);
			
			m_copyEffect = EffectManager().LoadEffect("Assets/presetShader/TransformedPrim.fx");
		}
	}
	
	void CDof::Render( CRenderContext& renderContext, CPostEffect* postEffect )
	{
		CPIXPerfTag tag(renderContext, L"CDof::Render");
		if (m_isEnable) {
			
			//被写体との距離から、こちらで計算する。
			static float CoC = 0.033f;			//許容錯乱円(単位はmm)
			float forwardDof = (CoC * m_F * m_pint * m_pint) / (m_focalLength * m_focalLength + CoC * m_F * m_pint);
			float backDof = (CoC * m_F * m_pint * m_pint) / (m_focalLength * m_focalLength - CoC * m_F * m_pint);
			//手前ボケ、奥ボケ、ピントをm単位に変更してGPUに送る
			float dofParam[] = {
				forwardDof / 1000.0f,
				backDof / 1000.0f,
				m_pint / 1000.0f
			};

			//ボケ画像を作成する。
			//奥ボケ
			{
				CPIXPerfTag tag(renderContext, L"CDof::Render(back blur)");
				m_blurBack.SetSrcTexture(*Engine().GetMainRenderTarget().GetTexture());
				m_blurBack.Draw(renderContext);
			}
			//手前ボケ
			{
				CPIXPerfTag tag(renderContext, L"CDof::Render(forward blur)");
				m_blurForward.SetSrcTexture(*Engine().GetMainRenderTarget().GetTexture());
				m_blurForward.Draw(renderContext);
			}
			
			//手前ボケと奥ボケを合成。
			{
				CPIXPerfTag tag(renderContext, L"CDof::Render(CombineBackForwardBoke)");
				m_effect->SetTechnique(renderContext, "CombineBackForwardBoke");
				m_effect->Begin(renderContext);
				m_effect->BeginPass(renderContext, 0);
				m_effect->SetValue(renderContext, "g_dofParam", dofParam, sizeof(dofParam));
				m_effect->SetTexture(renderContext, "g_depthTexture", m_depthRT.GetTexture());
				m_effect->SetTexture(renderContext, "g_blurBack", m_blurBack.GetTexture());
				m_effect->SetTexture(renderContext, "g_blurForward", m_blurForward.GetTexture());

				float texSize[] = {
					s_cast<float>(m_combineRenderTarget.GetWidth()),
					s_cast<float>(m_combineRenderTarget.GetHeight()),
				};
				m_effect->SetValue(renderContext, "g_rtSize", texSize, sizeof(texSize));
				m_effect->CommitChanges(renderContext);

				renderContext.SetRenderTarget(0, &m_combineRenderTarget);
				renderContext.Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
					D3DCOLOR_RGBA(0, 0, 255, 0), 1.0f, 0
					);
				postEffect->RenderFullScreen(renderContext);
				m_effect->EndPass(renderContext);
				m_effect->End(renderContext);
			}
			//ボケ画像とシーンを合成
			{
				CPIXPerfTag tag(renderContext, L"CDof::Render(Final)");
				renderContext.SetRenderTarget(0, &Engine().GetMainRenderTarget());
				m_copyEffect->SetTechnique(renderContext, "TransformedPrim");
				m_copyEffect->Begin(renderContext);
				m_copyEffect->BeginPass(renderContext, 0);
				float offset[] = {
					0.5f/s_cast<float>(Engine().GetMainRenderTarget().GetWidth()),
					0.5f/s_cast<float>(Engine().GetMainRenderTarget().GetHeight()),
				};
				m_copyEffect->SetValue(renderContext, "g_texelOffset", offset, sizeof(offset));
				m_copyEffect->SetTexture(renderContext, "g_tex", m_combineRenderTarget.GetTexture());
				m_copyEffect->CommitChanges(renderContext);
				renderContext.SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
				renderContext.SetRenderState(D3DRS_SRCBLEND, BLEND_SRCALPHA);
				renderContext.SetRenderState(D3DRS_DESTBLEND, BLEND_INVSRCALPHA);

				postEffect->RenderFullScreen(renderContext);

				m_copyEffect->EndPass(renderContext);
				m_copyEffect->End(renderContext);

				renderContext.SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
			}
		}
	}
}
