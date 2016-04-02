/*!
 * @brief	IDMap
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/preRender/tkIDMap.h"

namespace tkEngine{

	CIDMap::CIDMap()
	{
	}
	CIDMap::~CIDMap()
	{
		Release();
	}
	void CIDMap::Create(u32 w, u32 h)
	{
		m_idMapRT.Create( w, h, 1, FMT_A8, FMT_D16, MULTISAMPLE_NONE, 0);
	}
	void CIDMap::Release()
	{
		m_idMapRT.Release();
	}
	void CIDMap::RenderToIDMap( CRendeContext& renderContext )
	{
		CRenderTarget* pRTBackup = renderContext.GetRenderTarget();
		
		renderContext.SetRenderTarget
	}
}
