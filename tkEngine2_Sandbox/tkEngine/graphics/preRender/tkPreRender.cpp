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
		Release();
	}
	void CPreRender::Release()
	{
	}
	void CPreRender::Create( const SGraphicsConfig& config )
	{
		m_zprepass.Init();
		m_lightCulling.Init();
		m_shadowMap.Init(config.shadowRenderConfig);
	}
	/*!
	* @brief	描画。
	*/
	void CPreRender::Render(CRenderContext& rc)
	{
		m_zprepass.Render(rc);
		m_lightCulling.Render(rc);
	}

}

