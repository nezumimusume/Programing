/*!
 * @brief	ボックス
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/shape/tkBoxShape.h"

namespace tkEngine{
	CBoxShape::CBoxShape() 
	{
	}
	CBoxShape::~CBoxShape()
	{
		Release();
	}
	void CBoxShape::Create( CVector3 size, u32 color )
	{
		Release();
		m_isCreatePrimitive = true;
		CVector3 halfSize = size;
		halfSize.Scale(0.5f);
		SShapeVertex_PC vertex[] = {
			//前面
			{
				-halfSize.x, halfSize.y, -halfSize.z, 1.0f,
				color,
			},
			{
				halfSize.x, halfSize.y, -halfSize.z, 1.0f,
				color,
			},
			{
				halfSize.x, -halfSize.y, -halfSize.z, 1.0f,
				color,
			},
			{
				-halfSize.x, -halfSize.y, -halfSize.z, 1.0f,
				color,
			},
			{
				-halfSize.x, halfSize.y, -halfSize.z, 1.0f,
				color,
			},
			{
				halfSize.x, -halfSize.y, -halfSize.z, 1.0f,
				color,
			},
			//裏面。
			{
				halfSize.x, halfSize.y, halfSize.z, 1.0f,
				color,
			},
			{
				-halfSize.x, halfSize.y, halfSize.z, 1.0f,
				color,
			},
			{
				-halfSize.x, -halfSize.y, halfSize.z, 1.0f,
				color,
			},
			{
				halfSize.x, -halfSize.y, halfSize.z, 1.0f,
				color,
			},
			{
				halfSize.x, halfSize.y, halfSize.z, 1.0f,
				color,
			},
			{
				-halfSize.x, -halfSize.y, halfSize.z, 1.0f,
				color,
			},
			//左面。
			{
				-halfSize.x, -halfSize.y, halfSize.z, 1.0f,
				color 
			},
			{
				-halfSize.x, halfSize.y, halfSize.z, 1.0f,
				color 
			},
			{
				-halfSize.x, -halfSize.y, -halfSize.z, 1.0f,
				color 
			},
			{
				-halfSize.x, -halfSize.y, -halfSize.z, 1.0f,
				color 
			},
			{
				-halfSize.x, halfSize.y, halfSize.z, 1.0f,
				color 
			},
			{
				-halfSize.x, halfSize.y, -halfSize.z, 1.0f,
				color 
			},
			//右面
			{
				halfSize.x, -halfSize.y, -halfSize.z, 1.0f,
				color
			},
			{
				halfSize.x, halfSize.y, -halfSize.z, 1.0f,
				color
			},
			{
				halfSize.x, -halfSize.y, halfSize.z, 1.0f,
				color
			},
			{
				halfSize.x, -halfSize.y, halfSize.z, 1.0f,
				color
			},
			{
				halfSize.x, halfSize.y, -halfSize.z, 1.0f,
				color
			},
			{
				halfSize.x, halfSize.y, halfSize.z, 1.0f,
				color
			},
			//下面
			{
				-halfSize.x, -halfSize.y, halfSize.z, 1.0f,
				color
			},
			{
				-halfSize.x, -halfSize.y, -halfSize.z, 1.0f,
				color
			},
			{
				halfSize.x, -halfSize.y, halfSize.z, 1.0f,
				color
			},
			{
				halfSize.x, -halfSize.y, halfSize.z, 1.0f,
				color
			},
			{
				-halfSize.x, -halfSize.y, -halfSize.z, 1.0f,
				color
			},
			{
				halfSize.x, -halfSize.y, -halfSize.z, 1.0f,
				color
			},
			//上面
			{
				halfSize.x, halfSize.y, halfSize.z, 1.0f,
				color
			},
			{
				halfSize.x, halfSize.y, -halfSize.z, 1.0f,
				color
			},
			{
				-halfSize.x, halfSize.y, halfSize.z, 1.0f,
				color
			},
			{
				-halfSize.x, halfSize.y, halfSize.z, 1.0f,
				color
			},
			{
				halfSize.x, halfSize.y, -halfSize.z, 1.0f,
				color
			},
			{
				-halfSize.x, halfSize.y, -halfSize.z, 1.0f,
				color
			},

		};
		static u16 index[] = {
			0,  1, 2, 3, 4, 5, 
			6,  7, 8, 9,10,11,
			12,13,14,15,16,17,
			18,19,20,21,22,23,
			24,25,26,27,28,29,
			30,31,32,33,34,35,
		};
		m_pPrimitive = new CPrimitive;
		m_pPrimitive->Create(
			CPrimitive::eTriangleList,
			sizeof(vertex) / sizeof(vertex[0]),
			sizeof(vertex[0]),
			eVertexFormat_diffuse | eVertexFormat_xyzw,
			vertex,
			sizeof(index) / sizeof(index[0]),
			eIndexFormat16,
			index
		);
	}
}
