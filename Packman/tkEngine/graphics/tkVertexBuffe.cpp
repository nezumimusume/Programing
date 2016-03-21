/*!
 * @brief	頂点バッファ
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkVertexBuffer.h"

namespace tkEngine{
	CVertexBuffer::CVertexBuffer() :
		m_pVB(nullptr)
	{
	}
	CVertexBuffer::~CVertexBuffer()
	{
		Release();
	}
	void CVertexBuffer::Create( u32 size, u32 format )
	{
		Release();

	}
	void CVertexBuffer::Release()
	{
		if(m_pVB != nullptr){
			m_pVB->Release();
		}
	}
}
