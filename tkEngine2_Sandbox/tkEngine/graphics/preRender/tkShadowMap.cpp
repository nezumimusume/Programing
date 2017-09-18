/*!
 * @brief	シャドウマップ。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/preRender/tkShadowMap.h"

namespace tkEngine{
	
	CShadowMap::CShadowMap()
	{
	}
	
	CShadowMap::~CShadowMap()
	{
	}
	
	bool CShadowMap::Init(const SShadowRenderConfig& config)
	{
		m_isEnable = config.isEnable;
		if (m_isEnable == false) {
			return true;
		}
		if(config.numShadowMap > MAX_SHADOW_MAP){
			TK_WARNING("numShadowMap is invalid");
			m_numShadowMap = MAX_SHADOW_MAP;
		}
		else {
			m_numShadowMap = config.numShadowMap;
		}
		
		int wh[MAX_SHADOW_MAP][2] = {
			{ config.shadowMapWidth, config.shadowMapHeight},
			{ config.shadowMapWidth >> 1, config.shadowMapWidth >> 1},
			{ config.shadowMapWidth >> 1, config.shadowMapWidth >> 1},
		};
		DXGI_SAMPLE_DESC multiSampleDesc;
		multiSampleDesc.Count = 1;
		multiSampleDesc.Quality = 0;
		for(int i = 0; i < m_numShadowMap; i++ ){
			m_shadowMapRT[i].Create(
				wh[i][0], 
				wh[i][1], 
				1, 
				DXGI_FORMAT_R16G16_FLOAT,
				DXGI_FORMAT_D24_UNORM_S8_UINT, 
				multiSampleDesc
			);
		}
		return true;
	}
}