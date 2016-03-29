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
		std::vector<SShapeVertex_PC> vertexBuffer;
		u32 numVertex = (grid + 1)*(grid + 1);
		vertexBuffer.reserve(numVertex);
		//球体形状の作成。
		f32 deltaAngle = 2.0f * CMath::PI / grid;
		for (u32 i = 0; i < grid+1; i++)
		{
			float y_angle = deltaAngle * i;
			for (u32 k = 0; k < grid+1; k++)
			{
				CVector3 t(0.0f, 0.0f, 0.0f);
				//Z軸周りの回転。
				float z_angle = deltaAngle * k;
				t.y = sin(z_angle);
				t.z = cos(z_angle);
				//Y軸周りの回転。
				t.x = t.z * sin(y_angle);
				t.z = t.z * cos(y_angle);
				t.Scale(radius);
				SShapeVertex_PC vtx;
				vtx.pos[0] = t.x;
				vtx.pos[1] = t.y;
				vtx.pos[2] = t.z;
				vtx.pos[3] = 1.0f;
				vtx.color = color;
				vertexBuffer.push_back(vtx);
			}
		}
		std::vector<u32>	indexBuffer;	//!<インデックスバッファ
		for (u32 i = 0; i < grid; i++) {
			u32 baseVertNo = (grid + 1) * i;
			u32 vertNo[3] = {
				baseVertNo ,
				baseVertNo + 1,
				baseVertNo + grid + 2
			};
			u32 vertNo2[3] = {
				baseVertNo + grid + 3,
				baseVertNo + grid + 2,
				baseVertNo + 2,
			};
			for (u32 k = 0; k < grid; k++) {
				if (k == 0) {
					indexBuffer.push_back(vertNo[0]);
					indexBuffer.push_back(vertNo[1]);
					indexBuffer.push_back(vertNo[2]);
					vertNo[0]++;
					vertNo[1]++;
				}
				else if (k == grid - 1) {
					indexBuffer.push_back(vertNo[1]);
					indexBuffer.push_back(vertNo[0]);
					indexBuffer.push_back(vertNo[2]);
				}else if (k != 0) {
					indexBuffer.push_back(vertNo[0]++);
					indexBuffer.push_back(vertNo[1]++);
					indexBuffer.push_back(vertNo[2]++);

					indexBuffer.push_back(vertNo2[0]++);
					indexBuffer.push_back(vertNo2[1]++);
					indexBuffer.push_back(vertNo2[2]++);
				}

			}
		}
		m_pPrimitive = new CPrimitive;
		m_pPrimitive->Create(
			CPrimitive::eTriangleList,
			numVertex,
			sizeof(SShapeVertex_PC),
			eVertexFormat_diffuse | eVertexFormat_xyzw,
			&vertexBuffer.at(0),
			indexBuffer.size(),
			eIndexFormat32,
			&indexBuffer.at(0)
			);
	}
}