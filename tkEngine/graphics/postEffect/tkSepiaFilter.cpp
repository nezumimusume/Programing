/*!
 * @brief	セピアフィルター。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/postEffect/tkSepiaFilter.h"
#include "tkEngine/graphics/tkEffect.h"

namespace tkEngine{
	CSepiaFilter::CSepiaFilter()
	{
		
	}
	CSepiaFilter::~CSepiaFilter()
	{
	}
	void CSepiaFilter::Create(const SGraphicsConfig& config)
	{
		m_effect = EffectManager().LoadEffect("Assets/presetShader/sepiaFilter.fx");
	}
}