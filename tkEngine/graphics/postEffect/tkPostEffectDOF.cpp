/*!
 * @brief	被写界深度。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/postEffect/tkPostEffectDOF.h"
#include "tkEngine/graphics/tkEffect.h"

namespace tkEngine{
	/*!
	 * @brief	コンストラクタ。
	 */
	CDof::CDof() :
		m_isEnable(false)
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
			//32bitでリッチにやってみる。
			m_depthRT.Create(w, h, 1, FMT_R32F, FMT_INVALID, MULTISAMPLE_NONE, 0);
			m_blurForward.Init(w, h, *Engine().GetMainRenderTarget().GetTexture());
			m_blurBack.Init(w, h, *Engine().GetMainRenderTarget().GetTexture());
			m_blurBack.SetBlurPower(1.0f);
			m_blurForward.SetBlurPower(10.0f);
			m_effect = EffectManager().LoadEffect("Assets/presetShader/dof.fx");
		}
	}
	
	void CDof::Render( CRenderContext& renderContext, CPostEffect* postEffect )
	{
		CPIXPerfTag tag(renderContext, L"CDof::Render");
		if (m_isEnable) {
			//ボケ用のパラメータをこちらで計算する。
			//被写体との距離から、こちらで計算する。
			//とりあえず適当。
			static float pint = 3000.0f;		//被写体までの距離(単位はmm)
			static float focalLength = 28.0f;	//焦点距離(単位はmm)
			static float f = 5.6f;				//絞り値
			static float CoC = 0.033f;			//許容錯乱円(単位はmm)
			float forwardDof = (CoC * f * pint * pint) / (focalLength * focalLength + CoC * f * pint);
			float backDof = (CoC * f * pint * pint) / (focalLength * focalLength - CoC * f * pint);
			//手前ボケ、奥ボケ、ピントをm単位に変更してGPUに送る
			
			
			float dofParam[] = {
				forwardDof / 1000.0f,
				backDof / 1000.0f,
				pint / 1000.0f
			};

			static float depth = 5.0f;
			float t = depth - dofParam[2];
			float forwardRate = max(0.0f, -dofParam[0] - t);
			float backRate = max(0.0f, t - dofParam[1]);
			t = max(forwardRate, backRate);
			t = min(t / (dofParam[2] - dofParam[0]), 1.0f);

			//ボケ画像を作成する。
			//奥ボケ
			m_blurBack.SetSrcTexture(*Engine().GetMainRenderTarget().GetTexture());
			m_blurBack.Draw(renderContext);
			//手前ボケ
			m_blurForward.SetSrcTexture(*Engine().GetMainRenderTarget().GetTexture());
			m_blurForward.Draw(renderContext);
			
			//合成。
			m_effect->SetTechnique(renderContext, "Dof");
			m_effect->Begin(renderContext);
			m_effect->BeginPass(renderContext, 0);
			m_effect->SetValue(renderContext, "g_dofParam", dofParam, sizeof(dofParam));
			m_effect->SetTexture(renderContext, "g_scene", Engine().GetMainRenderTarget().GetTexture());
			m_effect->SetTexture(renderContext, "g_depthTexture", m_depthRT.GetTexture());
			m_effect->SetTexture(renderContext, "g_blurBack", m_blurBack.GetTexture());
			m_effect->SetTexture(renderContext, "g_blurForward", m_blurForward.GetTexture());

			float texSize[] = {
				s_cast<float>(m_depthRT.GetWidth()),
				s_cast<float>(m_depthRT.GetHeight()),
			};
			m_effect->SetValue(renderContext, "g_sceneTexSize", texSize, sizeof(texSize));
			m_effect->CommitChanges(renderContext);
			postEffect->RenderFullScreen(renderContext);
			m_effect->EndPass(renderContext);
			m_effect->End(renderContext);

			
		}
	}
}
