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

}