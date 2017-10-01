/*!
 *@brief	トーンマップ。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/postEffect/tkTonemap.h"



namespace tkEngine{
	namespace {
		static const int MAX_SAMPLES = 16;
		//-----------------------------------------------------------------------------
		// Name: GetSampleOffsets_DownScale4x4
		// Desc: Get the texture coordinate offsets to be used inside the DownScale4x4
		//       pixel shader.
		//-----------------------------------------------------------------------------
		HRESULT GetSampleOffsets_DownScale4x4(DWORD dwWidth, DWORD dwHeight, CVector2 avSampleOffsets[])
		{
			if (NULL == avSampleOffsets)
				return E_INVALIDARG;

			float tU = 1.0f / dwWidth;
			float tV = 1.0f / dwHeight;

			// Sample from the 16 surrounding points. Since the center point will be in
			// the exact center of 16 texels, a 0.5f offset is needed to specify a texel
			// center.
			int index = 0;
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					avSampleOffsets[index].x = (x - 1.5f) * tU;
					avSampleOffsets[index].y = (y - 1.5f) * tV;

					index++;
				}
			}

			return S_OK;
		}
	}
	CTonemap::CTonemap()
	{
	}
	CTonemap::~CTonemap()
	{
	}
	void CTonemap::Create(const SGraphicsConfig& config)
	{
		if (config.tonemapConfig.isEnable) {
			m_isEnable = true;
			DXGI_SAMPLE_DESC multiSampleDesc;
			ZeroMemory(&multiSampleDesc, sizeof(multiSampleDesc));
			multiSampleDesc.Count = 1;
			multiSampleDesc.Quality = 0;
		//	m_effect = EffectManager().LoadEffect("Assets/presetShader/tonemap.fx");
			//平均輝度計算用のレンダリングターゲットを作成。
			for (int i = 0; i < NUM_CALC_AVG_RT; i++)
			{
				int rtSize = 1 << (2 * i);
				m_calcAvgRT[i].Create(
					rtSize,
					rtSize,
					1,
					1,
					DXGI_FORMAT_R16G16B16A16_FLOAT,
					DXGI_FORMAT_UNKNOWN,
					multiSampleDesc
				);
			}

			//最終的にトーンマップで使用する平均輝度を書き込むレンダリングターゲットを作成。
			for (auto& rt : m_avgRT) {
				rt.Create(
					1,
					1,
					1,
					1,
					DXGI_FORMAT_R16G16B16A16_FLOAT,
					DXGI_FORMAT_UNKNOWN,
					multiSampleDesc
				);
			}
		}
	}
	void CTonemap::CalcLuminanceAvarage(CRenderContext& renderContext, CPostEffect* postEffect)
	{
	/*	if (!m_isEnable) {
			return;
		}
		CGraphicsEngine& ge = Engine().GetGraphicsEngine();
		ge.BeginGPUEvent(L"CTonemap::CalcLuminanceAvarage");
		
		
		//対数平均を求める。

		CVector2 avSampleOffsets[MAX_SAMPLES];

		float tU, tV;
		tU = 1.0f / (3.0f * m_calcAvgRT[NUM_CALC_AVG_RT - 1].GetWidth());
		tV = 1.0f / (3.0f * m_calcAvgRT[NUM_CALC_AVG_RT - 1].GetHeight());

		int index = 0;
		for (int x = -1; x <= 1; x++)
		{
			for (int y = -1; y <= 1; y++)
			{
				avSampleOffsets[index].x = x * tU;
				avSampleOffsets[index].y = y * tV;

				index++;
			}
		}
			
		int curRtNo = NUM_CALC_AVG_RT - 1;
		{
			ge.BeginGPUEvent(L"CTonemap::CalcLuminanceLogAvarage");
			
			CRenderTarget* rts[] = {
				&m_calcAvgRT[curRtNo]
			};
			renderContext.OMSetRenderTargets(1, rts);
			m_effect->SetTechnique(renderContext, "CalcLuminanceLogAvarage");
			m_effect->Begin(renderContext);
			m_effect->BeginPass(renderContext, 0);
			m_effect->SetValue(renderContext, "g_avSampleOffsets", avSampleOffsets, sizeof(avSampleOffsets));
			m_effect->SetTexture(renderContext, "g_scene", Engine().GetMainRenderTarget().GetTexture());
			m_effect->CommitChanges(renderContext);
			postEffect->DrawFullScreenQuad(renderContext);
			m_effect->EndPass(renderContext);
			m_effect->End(renderContext);

			ge.EndGPUEvent();
		}
		//ダウンサンプリングを行って平均を求める。
		curRtNo--;
		{
			ge.BeginGPUEvent(L"CTonemap::CalcLuminanceAvarage");
			while (curRtNo > 0) {
				CRenderTarget* rts[] = {
					&m_calcAvgRT[curRtNo]
				};
				renderContext.OMSetRenderTargets(1, rts);
				GetSampleOffsets_DownScale4x4(m_calcAvgRT[curRtNo].GetWidth(), m_calcAvgRT[curRtNo].GetHeight(), avSampleOffsets);
				m_effect->SetTechnique(renderContext, "CalcLuminanceAvarage");
				m_effect->Begin(renderContext);
				m_effect->BeginPass(renderContext, 0);
				m_effect->SetValue(renderContext, "g_avSampleOffsets", avSampleOffsets, sizeof(avSampleOffsets));
				m_effect->SetTexture(renderContext, "g_scene", m_calcAvgRT[curRtNo + 1].GetTexture());

				m_effect->CommitChanges(renderContext);
				postEffect->DrawFullScreenQuad(renderContext);
				m_effect->EndPass(renderContext);
				m_effect->End(renderContext);
				curRtNo--;
			}
			ge.EndGPUEvent();
		}
		//exp関数を用いて最終平均を求める。
		CRenderTarget* rts[] = {
			&m_calcAvgRT[curRtNo]
		};
		renderContext.OMSetRenderTargets(1, rts);
		GetSampleOffsets_DownScale4x4(m_calcAvgRT[curRtNo].GetWidth(), m_calcAvgRT[curRtNo].GetHeight(), avSampleOffsets);
		{
			ge.BeginGPUEvent(L"CTonemap::CalcLuminanceExpAvarage");
			m_effect->SetTechnique(renderContext, "CalcLuminanceExpAvarage");
			m_effect->Begin(renderContext);
			m_effect->BeginPass(renderContext, 0);
			m_effect->SetValue(renderContext, "g_avSampleOffsets", avSampleOffsets, sizeof(avSampleOffsets));
			m_effect->SetTexture(renderContext, "g_scene", m_calcAvgRT[curRtNo + 1].GetTexture());

			m_effect->CommitChanges(renderContext);
			postEffect->DrawFullScreenQuad(renderContext);
			m_effect->EndPass(renderContext);
			m_effect->End(renderContext);

			ge.EndGPUEvent();
		}
		//明暗順応。
		{
			ge.BeginGPUEvent(L"CTonemap::CalcAdaptedLuminance");
			if (m_isFirstWhenChangeScene == true) {
				//シーンが切り替わって初回。
				m_currentAvgRT = 1 ^ m_currentAvgRT;
				CRenderTarget* rts[] = {
					&m_avgRT[m_currentAvgRT]
				};
				renderContext.OMSetRenderTargets(1, rts);
				m_effect->SetTechnique(renderContext, "CalcAdaptedLuminanceFirst");
				m_effect->Begin(renderContext);
				m_effect->BeginPass(renderContext, 0);
				m_effect->SetTexture(renderContext, "g_lumAvgTex", m_calcAvgRT[0].GetTexture());
				m_effect->CommitChanges(renderContext);
				postEffect->DrawFullScreenQuad(renderContext);
				m_effect->EndPass(renderContext);
				m_effect->End(renderContext);
				m_isFirstWhenChangeScene = false;
			}
			else {
					
				CRenderTarget& lastRT = m_avgRT[m_currentAvgRT];
				m_currentAvgRT = 1 ^ m_currentAvgRT;
				CRenderTarget* rts[] = {
					&m_avgRT[m_currentAvgRT]
				};
				renderContext.OMSetRenderTargets(1, rts);
				
				m_effect->SetTechnique(renderContext, "CalcAdaptedLuminance");
				m_effect->Begin(renderContext);
				m_effect->BeginPass(renderContext, 0);
				float deltaTime = GameTime().GetFrameDeltaTime();
				m_effect->SetValue(renderContext, "g_fElapsedTime", &deltaTime, sizeof(deltaTime));
				m_effect->SetTexture(renderContext, "g_lumAvgTex", m_calcAvgRT[0].GetTexture());
				m_effect->SetTexture(renderContext, "g_lastLumAvgTex", lastRT.GetTexture());
				m_effect->CommitChanges(renderContext);
				postEffect->DrawFullScreenQuad(renderContext);
				m_effect->EndPass(renderContext);
				m_effect->End(renderContext);
			}
			ge.EndGPUEvent();
		}
		ge.EndGPUEvent();*/
		
	}
	void CTonemap::Render(CRenderContext& renderContext, CPostEffect* postEffect)
	{
		if (!m_isEnable) {
			return;
		}
		/*renderContext.SetRenderStep(enRenderStep_Toonmap);
		CGraphicsEngine& ge = Engine().GetGraphicsEngine();
		ge.BeginGPUEvent(L"enRenderStep_Toonmap");
		
		const CTexture* sceneTex = Engine().GetMainRenderTarget().GetTexture();
		Engine().ToggleMainRenderTarget();
		renderContext.SetRenderTarget(0, &Engine().GetMainRenderTarget());
		renderContext.SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		renderContext.SetRenderState(D3DRS_ZENABLE, FALSE);
		m_effect->SetTechnique(renderContext, "Final");
		m_effect->Begin(renderContext);
		m_effect->BeginPass(renderContext, 0);
		m_effect->SetTexture(renderContext, "g_lumAvgTex", m_avgRT[m_currentAvgRT].GetTexture());
		m_effect->SetTexture(renderContext, "g_scene", sceneTex);
		m_effect->SetValue(renderContext, "g_fMiddleGray", &m_fMiddleGray, sizeof(m_fMiddleGray));
		m_effect->CommitChanges(renderContext);
		postEffect->DrawFullScreenQuad(renderContext);
		m_effect->EndPass(renderContext);
		m_effect->End(renderContext);
		renderContext.SetRenderState(D3DRS_ZENABLE, TRUE);

		ge.EndGPUEvent();
	//	renderContext.SetRenderState(RS_ALPHABLENDENABLE, TRUE);*/
	}
}