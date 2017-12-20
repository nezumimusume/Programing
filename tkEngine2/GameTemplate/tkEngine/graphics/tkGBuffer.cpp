/*!
 *@brief	G-Buffer
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkGBuffer.h"

namespace tkEngine{
	/*!
	*@brief	初期化。
	*/
	void CGBuffer::Init()
	{
		CGraphicsEngine& ge = GraphicsEngine();
		DXGI_SAMPLE_DESC multiSampleDesc;
		ZeroMemory(&multiSampleDesc, sizeof(multiSampleDesc));
		multiSampleDesc.Count = 1;
		multiSampleDesc.Quality = 0;
		//法線バッファの初期化。
		m_GBuffer[enGBufferNormal].Create(
			ge.GetFrameBufferWidth(),
			ge.GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_SNORM,
			DXGI_FORMAT_UNKNOWN,
			multiSampleDesc
		);
	}
}