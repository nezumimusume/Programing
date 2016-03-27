/*!
 * @brief	プリミティブ。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkPrimitive.h"

namespace tkEngine{
#ifdef _DEBUG
	#define CHECK_VALIDATION	CheckValidation
#endif // _DEBUG
	CPrimitive::CPrimitivex() :
		m_numVertex(0),
		m_numIndex(0),
		m_vertexStride(0)
	{
	}
	CPrimitive::~CPrimitive()
	{
		Release();
	}
	void CPrimitive::Create( 
		EType 			primitiveType,
		u32 			numVertex,
		u32 			vertexStride,
		void*			pSrcVertexBuffer,
		u32 			numIndex,
		EIndexFormat	indexFormat,
		void*			pSrcIndexbuffer
	)
	{
		TK_ASSERT( primitiveType < eTypeNum, "primitiveType is invalid" );
		TK_ASSERT( numVertex != 0, "numVertex is zero" );
		TK_ASSERT( vertexStride != 0, "vertexStrid is zero" );
		TK_ASSERT( numIndex != 0, "numIndex is zero" );
		Release();
		m_vertexBuffer.Create( numVertex * vertexStride, pSrcVertexBuffer );
		m_indexBuffer.Create( numIndex, indexFormat, pSrcIndexbuffer );
		if(primitiveType == eTriangleList){
			m_numPolygon = numIndex / 3;
		}else if(primitiveType == eTriangleStrip){
			m_numPolygon = numIndex - 2;
		}
	}
	void CPrimitive::Release()
	{
		m_vertexBuffer.Release();
		m_indexBuffer.Release();
	}
}