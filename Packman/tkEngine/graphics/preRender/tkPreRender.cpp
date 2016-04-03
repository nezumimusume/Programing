/*!
 * @brief	プリレンダリング。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/preRender/tkPreRender.h"

namespace tkEngine{
	CPreRender::CPreRender()
	{
	}
	CPreRender::~CPreRender()
	{
	}
	void CPreRender::Create( const SGraphicsConfig& config )
	{
		if (config.edgeRenderConfig.isEnable) {
			m_idMap.Create(config.edgeRenderConfig.idMapWidth, config.edgeRenderConfig.idMapHeight);
		}
		if (config.shadowRenderConfig.isEnable) {
			m_shadowMap.Create(config.shadowRenderConfig.shadowMapWidth, config.shadowRenderConfig.shadowMapHeight);
		}
	}
}

