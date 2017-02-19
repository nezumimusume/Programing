/*!
 * @brief	ブルーム
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/postEffect/tkBloomRender.h"
#include "tkEngine/graphics/tkEffect.h"
#include "tkEngine/graphics/tkRenderTarget.h"

namespace tkEngine{
	/*!
	 * @brief	コンストラクタ。
	 */
	CBloomRender::CBloomRender()
	{
	}
	/*!
	 * @brief	デストラクタ。
	 */
	CBloomRender::~CBloomRender()
	{
	}
	void CBloomRender::UpdateWeight(float dispersion)
	{
		float total = 0;
		for (int i = 0; i<NUM_WEIGHTS; i++) {
			m_weights[i] = expf(-0.5f*(float)(i*i) / dispersion);
			total += 2.0f*m_weights[i];
			
		}
		// 規格化
		for (int i = 0; i < NUM_WEIGHTS; i++) {
			m_weights[i] /= total;
		}
	}
	/*!
	 * @brief	描画。
	 */
	void CBloomRender::Render( CRenderContext& renderContext, CPostEffect* postEffect )
	{
		CPIXPerfTag tag(renderContext, L"CBloomRender::Render");
		if (m_isEnable) {
			UpdateWeight(25.0f);
			CRenderTarget* rt = renderContext.GetRenderTarget(0);
			
			//輝度抽出
			{
				renderContext.SetRenderTarget(0, &m_luminanceRenderTarget);
				renderContext.Clear(0, nullptr, D3DCLEAR_TARGET , 0, 1.0f, 0);
				m_pEffect->SetTechnique(renderContext, "SamplingLuminance");
				m_pEffect->Begin(renderContext);
				m_pEffect->BeginPass(renderContext, 0);
				m_pEffect->SetTexture(renderContext, "g_scene", rt->GetTexture());
				m_pEffect->CommitChanges(renderContext);
				postEffect->RenderFullScreen(renderContext);

				m_pEffect->EndPass(renderContext);
				m_pEffect->End(renderContext);
				
			}
			//輝度をぼかす。
			CRenderTarget* prevRenderTarget = &m_luminanceRenderTarget;
			int rtIndex = 0;
			for (int i = 0; i < NUM_DOWN_SAMPLING_RT / 2; i++) {
				
				//XBlur
				{
					renderContext.SetRenderTarget(0, &m_downSamplingRenderTarget[rtIndex]);
					renderContext.Clear(0, nullptr, D3DCLEAR_TARGET, 0, 1.0f, 0);
					m_pEffect->SetTechnique(renderContext, "XBlur");
					m_pEffect->Begin(renderContext);
					m_pEffect->BeginPass(renderContext, 0);
					float size[2] = {
						s_cast<float>(prevRenderTarget->GetWidth()),
						s_cast<float>(prevRenderTarget->GetHeight())
					};
					float offset[] = {
						16.0f / s_cast<float>(prevRenderTarget->GetWidth()),
						0.0f
					};
					float renderTargetSize[2] = {
						(float)m_downSamplingRenderTarget[rtIndex].GetWidth(),
						(float)m_downSamplingRenderTarget[rtIndex].GetHeight()
					};
					m_pEffect->SetValue(renderContext, "g_luminanceTexSize", size, sizeof(size));
					m_pEffect->SetValue(renderContext, "g_offset", offset, sizeof(size));
					m_pEffect->SetValue(renderContext, "g_weight", m_weights, sizeof(m_weights));
					m_pEffect->SetValue(renderContext, "g_renderTargetSize", renderTargetSize, sizeof(renderTargetSize));
					m_pEffect->SetTexture(renderContext, "g_blur", prevRenderTarget->GetTexture());
					m_pEffect->CommitChanges(renderContext);
					postEffect->RenderFullScreen(renderContext);

					m_pEffect->EndPass(renderContext);
					m_pEffect->End(renderContext);
				}
				prevRenderTarget = &m_downSamplingRenderTarget[rtIndex];
				rtIndex++;
				//YBlur
				{
					renderContext.SetRenderTarget(0, &m_downSamplingRenderTarget[rtIndex]);
					renderContext.Clear(0, nullptr, D3DCLEAR_TARGET, 0, 1.0f, 0);
					m_pEffect->SetTechnique(renderContext, "YBlur");
					m_pEffect->Begin(renderContext);
					m_pEffect->BeginPass(renderContext, 0);
					float size[2] = {
						s_cast<float>(prevRenderTarget->GetWidth()),
						s_cast<float>(prevRenderTarget->GetHeight())
					};
					float offset[] = {
						0.0f,
						16.0f / s_cast<float>(prevRenderTarget->GetHeight()),
					};
					float renderTargetSize[2] = {
						(float)m_downSamplingRenderTarget[rtIndex].GetWidth(),
						(float)m_downSamplingRenderTarget[rtIndex].GetHeight()
					};
					m_pEffect->SetValue(renderContext, "g_luminanceTexSize", size, sizeof(size));
					m_pEffect->SetValue(renderContext, "g_offset", offset, sizeof(offset));
					m_pEffect->SetValue(renderContext, "g_weight", m_weights, sizeof(m_weights));
					m_pEffect->SetValue(renderContext, "g_renderTargetSize", renderTargetSize, sizeof(renderTargetSize));
					m_pEffect->SetTexture(renderContext, "g_blur", prevRenderTarget->GetTexture());
					m_pEffect->CommitChanges(renderContext);
					postEffect->RenderFullScreen(renderContext);

					m_pEffect->EndPass(renderContext);
					m_pEffect->End(renderContext);
				}
				prevRenderTarget = &m_downSamplingRenderTarget[rtIndex];
				rtIndex++;
			}
			{
				//ボケフィルターの合成。
				renderContext.SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
				renderContext.SetRenderTarget(0, &m_combineRenderTarget);
				renderContext.Clear(0, nullptr, D3DCLEAR_TARGET, 0, 1.0f, 0);
				float offset[] = {
					0.5f / s_cast<float>(m_combineRenderTarget.GetWidth()),
					0.5f / s_cast<float>(m_combineRenderTarget.GetHeight()),
				};
				m_pEffect->SetTechnique(renderContext, "Combine");
				m_pEffect->Begin(renderContext);
				m_pEffect->BeginPass(renderContext, 0);
				
				m_pEffect->SetTexture(renderContext, "g_combineTex00", m_downSamplingRenderTarget[1].GetTexture());
				m_pEffect->SetTexture(renderContext, "g_combineTex01", m_downSamplingRenderTarget[3].GetTexture());
				m_pEffect->SetTexture(renderContext, "g_combineTex02", m_downSamplingRenderTarget[5].GetTexture());
				m_pEffect->SetTexture(renderContext, "g_combineTex03", m_downSamplingRenderTarget[7].GetTexture());
				m_pEffect->SetTexture(renderContext, "g_combineTex04", m_downSamplingRenderTarget[9].GetTexture());
				m_pEffect->SetValue(renderContext, "g_offset", offset, sizeof(offset));

				m_pEffect->CommitChanges(renderContext);
				postEffect->RenderFullScreen(renderContext);

				m_pEffect->EndPass(renderContext);
				m_pEffect->End(renderContext);
			}

			{
				float offset[] = {
					0.5f / m_combineRenderTarget.GetWidth() ,
					0.5f / m_combineRenderTarget.GetHeight()
				};
				//戻す。
				renderContext.SetRenderTarget(0, rt);
				//加算合成。
				renderContext.SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
				renderContext.SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
				renderContext.SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
				m_pEffect->SetTechnique(renderContext, "Final");
				m_pEffect->Begin(renderContext);
				m_pEffect->BeginPass(renderContext, 0);
				m_pEffect->SetTexture(renderContext, "g_blur", m_combineRenderTarget.GetTexture());
				m_pEffect->SetValue(renderContext, "g_offset", offset, sizeof(offset));
				m_pEffect->CommitChanges(renderContext);
				postEffect->RenderFullScreen(renderContext);

				m_pEffect->EndPass(renderContext);
				m_pEffect->End(renderContext);

				renderContext.SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
				renderContext.SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				renderContext.SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			}
		}

	}
	/*!
	* @brief	開放。
	*/
	void CBloomRender::Release()
	{
		m_luminanceRenderTarget.Release();
		for (int i = 0; i < NUM_DOWN_SAMPLING_RT; i++) {
			m_downSamplingRenderTarget[i].Release();
		}
	}
	/*!
	 * @brief	作成。
	 */
	void CBloomRender::Create( const SGraphicsConfig& config )
	{
		if (config.bloomConfig.isEnable) {
			int w = CEngine::Instance().GetFrameBufferWidth();
			int h = CEngine::Instance().GetFrameBufferHeight();
			//輝度抽出用のレンダリングターゲットを作成。
			m_luminanceRenderTarget.Create(w, h, 1, D3DFMT_A16B16G16R16F, D3DFMT_UNKNOWN, D3DMULTISAMPLE_NONE, 0);
			//ダウンサンプリング用のレンダリングターゲットを作成。
			
			for (int i = 0; i < NUM_DOWN_SAMPLING_RT/2; i++) {
				int shift = i + 1;
				int baseIndex = i * 2;
				m_downSamplingRenderTarget[baseIndex].Create(w >> shift, h >> (shift -1), 1, D3DFMT_A16B16G16R16F, D3DFMT_UNKNOWN, D3DMULTISAMPLE_NONE, 0);			//横ブラー用。
				m_downSamplingRenderTarget[baseIndex+1].Create(w >> shift, h >> shift, 1, D3DFMT_A16B16G16R16F, D3DFMT_UNKNOWN, D3DMULTISAMPLE_NONE, 0);	//縦ブラー用。
			}
			m_combineRenderTarget.Create(w >> 2, h >> 2, 1, D3DFMT_A16B16G16R16F, D3DFMT_UNKNOWN, D3DMULTISAMPLE_NONE, 0);				//ぼかし合成用
			m_pEffect = CEngine::Instance().EffectManager().LoadEffect("Assets/presetShader/bloom.fx");
			m_isEnable = true;
		}
	}
}
