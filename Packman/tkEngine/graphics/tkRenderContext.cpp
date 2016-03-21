#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkRenderContext.h"


namespace tkEngine{
	void CRenderContext::Init(LPDIRECT3DDEVICE9 pD3DDevice, u32 commandBufferSize)
	{
		TK_ASSERT( pD3DDevice != NULL, "pD3DDevice is NULL!!!" );
		m_pD3DDevice = pD3DDevice;
		m_commandBuffer.Init( commandBufferSize );
	}
}

