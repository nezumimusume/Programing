/*!
 *@brief	ポストエフェクト。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/postEffect/tkPostEffect.h"

namespace tkEngine{
	namespace {
		struct SSimpleVertex {
			CVector4 pos;
			CVector2 tex;
		};
	}
	CPostEffect::CPostEffect()
	{
	}
	CPostEffect::~CPostEffect()
	{
		Release();
	}
	void CPostEffect::Release()
	{
		m_fullscreenQuad.Release();
	}
	void CPostEffect::Create( const SGraphicsConfig& config )
	{
		Release();
		m_fxaa.Init(config);
		InitFullScreenQuadPrimitive();
	}
	void CPostEffect::Render(CRenderContext& rc)
	{
		m_fxaa.Render(rc);
	}
	void CPostEffect::InitFullScreenQuadPrimitive()
	{
		//頂点バッファのソースデータ。
		SSimpleVertex vertices[] =
		{
			{
				CVector4(-1.0f, -1.0f, 0.0f, 1.0f),
				CVector2(0.0f, 1.0f),
			},
			{
				CVector4(1.0f, -1.0f, 0.0f, 1.0f),
				CVector2(1.0f, 1.0f),
			},
			{
				CVector4(-1.0f, 1.0f, 0.0f, 1.0f),
				CVector2(0.0f, 0.0f)
			},
			{
				CVector4(1.0f, 1.0f, 0.0f, 1.0f),
				CVector2(1.0f, 0.0f)
			}

		};
		short indices[] = { 0,1,2,3 };
		
		m_fullscreenQuad.Create(
			D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
			4,
			sizeof(SSimpleVertex),
			vertices,
			4,
			CIndexBuffer::enIndexType_16,
			indices
		);
	}
	void CPostEffect::DrawFullScreenQuad(CRenderContext& rc)
	{
		m_fullscreenQuad.Draw(rc);
	}
}