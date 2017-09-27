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
}