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
	void CSphereShape::Create(f32 radius, f32 grid, u32 color)
	{
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
				t.x = cos(angle) + t.z * sin(angle);
				t.z = -sin(angle) + t.z * cos(angle);
				ShapeVertex_Color vtx;
				vtx.pos[0] = t.x;
				vtx.pos[1] = t.y;
				vtx.pos[2] = t.z;
				vtx.pos[3] = 1.0f;
				vtx.color = color;
				vertexBuffer.push_back(vtx);
			}
		}
	}
}