/*!
 * @brief	�v�������_�����O�B
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
	}
	/*!
	* @brief	�`��B
	*/
	void CPreRender::Render(CRenderContext& rc)
	{
		m_zprepass.Render(rc);
		m_lightCulling.Render(rc);
	}

}
