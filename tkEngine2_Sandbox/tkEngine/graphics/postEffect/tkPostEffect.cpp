/*!
 *@brief	ポストエフェクト。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/postEffect/tkPostEffect.h"

namespace tkEngine{
	CPostEffect::CPostEffect()
	{
	}
	CPostEffect::~CPostEffect()
	{
	}
	void CPostEffect::Release()
	{
	}
	void CPostEffect::Create( const SGraphicsConfig& config )
	{
		Release();
	}
	void CPostEffect::Render(CRenderContext& rc)
	{
		m_fxaa.Render(rc);
	}
}