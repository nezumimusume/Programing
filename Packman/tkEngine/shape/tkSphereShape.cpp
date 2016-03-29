/*!
 *@brief	球
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/shape/tkSphereShape.h"
#include <vector>
namespace tkEngine {
	CSphereShape::CSphereShape()
	{
	}
	CSphereShape::~CSphereShape() 
	{
	}
	void CSphereShape::Create(f32 radius, u32 grid, u32 color)
	{
		Release();
		m_isCreatePrimitive = true;
		std::vector<ShapeVertex_Color> vertexBuffer;
		u32 numVertex = (grid + 1)*(grid + 1);
		vertexBuffer.reserve(numVertex);
		//球体形状の作成。
		f32 deltaAngle = 2.0f * CMath::PI / grid;
		for (u32 i = 0; i < grid; i++) 
		{
			for (u32 k = 0; k < grid; k++)
			{
				CVector3 t(0.0f, 0.0f, 0.0f);
				//Z軸周りの回転。
				float angle = deltaAngle * k;
				t.y = sin(angle);
				t.z = cos(angle);
				//Y軸周りの回転。
				t.x = t.z * sin(angle);
				t.z = t.z * cos(angle);
				t.Scale(radius);
				ShapeVertex_Color vtx;
				vtx.pos[0] = t.x;
				vtx.pos[1] = t.y;
				vtx.pos[2] = t.z;
				vtx.pos[3] = 1.0f;
				vtx.color = color;
				vertexBuffer.push_back(vtx);
			}
		}
		std::vector<u32>	indexBuffer;	//!<インデックスバッファ
		u32 vertNo[3] = {0, 1, grid+2};
		for( u32 k = 0; k < grid+2; k++ ){
			if (k != 0) {
				u32 vertNoTmp[3] = { vertNo[0], vertNo[1], vertNo[2] };
				if (k % 2 != 0) {
					//奇数
					vertNo[0] = vertNoTmp[1];
					vertNo[1] = vertNoTmp[2];
					vertNo[2] = vertNoTmp[1] + 1;
				}
				else {
					//偶数
					vertNo[0] = vertNoTmp[1];
					vertNo[1] = vertNoTmp[1] + 1;
					vertNo[2] = vertNoTmp[2];
				}
			}
			indexBuffer.push_back(vertNo[0]);
			indexBuffer.push_back(vertNo[1]);
			indexBuffer.push_back(vertNo[2]);
		}
		m_pPrimitive = new CPrimitive;
		m_pPrimitive->Create(
			CPrimitive::eTriangleList,
			numVertex,
			sizeof(ShapeVertex_Color),
			eVertexFormat_diffuse | eVertexFormat_xyzw,
			&vertexBuffer.at(0),
			indexBuffer.size(),
			eIndexFormat32,
			&indexBuffer.at(0)
		);
	}
}