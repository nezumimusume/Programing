/*!
 * @brief	ガウシアンブラー。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkGaussianBlur.h"
#include "tkEngine/shape/tkShapeVertex.h"
#include "tkEngine/graphics/tkEffect.h"

namespace tkEngine {
	CGaussianBlur::CGaussianBlur() :
		m_srcTexture(nullptr)
	{

	}
	CGaussianBlur::~CGaussianBlur()
	{

	}
	void CGaussianBlur::UpdateWeight(float dispersion)
	{
		float total = 0;
		// ガウス関数による重みの計算
		for (int i = 0; i<NUM_WEIGHTS; i++)
		{
			float pos = (float)i * 2.0f;
			m_weights[i] = expf(-pos * pos * dispersion);
			total += m_weights[i];
		}

		// 重みの規格化
		for (int i = 0; i<NUM_WEIGHTS; i++)
			m_weights[i] = m_weights[i] / total * 0.5f;

	}
	void CGaussianBlur::Init(int w, int h, const CTexture& srcTexture)
	{
		m_srcTexture = &srcTexture;
		LPDIRECT3DTEXTURE9 tex = m_srcTexture->GetTextureDX();
		D3DSURFACE_DESC desc;
		tex->GetLevelDesc(0, &desc);
		m_srcTexWH[0] = w;
		m_srcTexWH[1] = h;
		int size[2][2]{
			{w >> 1, h},
			{ w >> 1, h >> 1},
		};
		for (int i = 0; i < 2; i++) {
			m_rt[i].Create(size[i][0], size[i][1], 1, (EFormat)desc.Format, FMT_D16, MULTISAMPLE_NONE, 0);
		}
		
		static SShapeVertex_PT vertex[]{
			{
				-1.0f, 1.0f, 0.0f, 1.0f,
				0.0f, 0.0f
			},
			{
				1.0f, 1.0f, 0.0f, 1.0f,
				1.0f, 0.0f
			},
			{
				-1.0f, -1.0f, 0.0f, 1.0f,
				0.0f, 1.0f
			},
			{
				1.0f, -1.0f, 0.0f, 1.0f,
				1.0f, 1.0f
			},
		};
		static unsigned short index[] = {
			0,1,2,3
		};
		m_prim.Create(
			CPrimitive::eTriangleStrip,
			4,
			sizeof(SShapeVertex_PT),
			scShapeVertex_PT_Element,
			vertex,
			4,
			eIndexFormat16,
			index
			);
		m_effect = EffectManager().LoadEffect("Assets/presetShader/TransformedPrim.fx");
		UpdateWeight(0.01f);
	}
	void CGaussianBlur::Draw(CRenderContext& renderContext)
	{
		CRenderTarget* rtBackup = renderContext.GetRenderTarget(0);

		//Xブラー。
		{
			renderContext.SetRenderTarget(0, &m_rt[0]);
			renderContext.Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
			float offset[] = {
				16.0f / m_srcTexWH[0],
				0.0f
			};
			float size[2] = {
				s_cast<float>(m_srcTexWH[0]),
				s_cast<float>(m_srcTexWH[1])
			};
			m_effect->SetTechnique(renderContext, "TransformedPrimGaussianBlurX");
			m_effect->Begin(renderContext);
			m_effect->BeginPass(renderContext, 0);
			m_effect->SetTexture(renderContext, "g_tex", m_srcTexture);
			m_effect->SetValue(renderContext, "g_texSize", size, sizeof(size));
			m_effect->SetValue(renderContext, "g_weight", m_weights, sizeof(m_weights));
			m_effect->SetValue(renderContext, "g_offset", offset, sizeof(offset));
			m_effect->CommitChanges(renderContext);
			renderContext.SetVertexDeclaration(m_prim.GetVertexDecl());
			renderContext.SetStreamSource(0, m_prim.GetVertexBuffer());
			renderContext.SetIndices(m_prim.GetIndexBuffer());
			renderContext.DrawIndexedPrimitive(&m_prim);

			m_effect->EndPass(renderContext);
			m_effect->End(renderContext);
		}
		//Yブラー。
		{
			renderContext.SetRenderTarget(0, &m_rt[1]);
			renderContext.Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
			float offset[] = {
				0.0f,
				16.0f / s_cast<float>(m_rt[0].GetHeight())
			};
			float size[2] = {
				s_cast<float>(m_rt[0].GetWidth()),
				s_cast<float>(m_rt[0].GetHeight())
			};
			m_effect->SetTechnique(renderContext, "TransformedPrimGaussianBlurY");
			m_effect->Begin(renderContext);
			m_effect->BeginPass(renderContext, 0);
			m_effect->SetTexture(renderContext, "g_tex", m_rt[0].GetTexture());
			m_effect->SetValue(renderContext, "g_texSize", size, sizeof(size));
			m_effect->SetValue(renderContext, "g_weight", m_weights, sizeof(m_weights));
			m_effect->SetValue(renderContext, "g_offset", offset, sizeof(offset));
			m_effect->CommitChanges(renderContext);
			renderContext.SetVertexDeclaration(m_prim.GetVertexDecl());
			renderContext.SetStreamSource(0, m_prim.GetVertexBuffer());
			renderContext.SetIndices(m_prim.GetIndexBuffer());
			renderContext.DrawIndexedPrimitive(&m_prim);

			m_effect->EndPass(renderContext);
			m_effect->End(renderContext);
		}
		renderContext.SetRenderTarget(0, rtBackup);

		//Yブラー。
	}
}