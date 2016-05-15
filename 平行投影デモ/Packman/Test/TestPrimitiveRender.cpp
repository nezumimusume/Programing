/*!
 * @brief	プリミティブ描画テスト。
 */
#include "stdafx.h"
#include "TestPrimitiveRender.h"
#include "tkEngine/shape/tkShapeVertex.h"

using namespace tkEngine;

namespace {
	struct SColorVertex {
		float			posision[4];
		DWORD		color;
	};
}
void CTestPrimitiveRender::Start() 
{
	//プリミティブを初期化。
	{
		SColorVertex vertex[] = {
			{
				10.0f, 10.0f, 0.0f, 1.0f,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			},
			{
			    10.0f, -10.0f, 0.0f, 1.0f,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			},
			{
				-10.0f, 10.0f, 0.0f, 1.0f,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			},
			{
				-10.0f, -10.0f, 0.0f, 1.0f,
				D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)
			},
		};
		unsigned short index[] = {
			0, 1, 2, 3
		};
		m_primitive.Create(
			CPrimitive::eTriangleStrip, 
			4, 
			sizeof(SColorVertex), 
			scShapeVertex_PC_Element,
			vertex, 
			4, 
			eIndexFormat16, 
			index
		);
	}
	//カメラを初期化
	{
		CVector3 cameraPos;
		CVector3 cameraTarget;
		cameraPos.Set(0.0f, 0.0f, -100.0f);
		cameraTarget = cameraPos;
		cameraTarget.z = 0.0f;
		m_camera.SetPosition( cameraPos );
		m_camera.SetTarget(CVector3::Zero);
		m_camera.SetUp(CVector3::Up);
		m_camera.SetFar(100000.0f);
		m_camera.SetNear(0.1f);
		m_camera.SetViewAngle(CMath::DegToRad(45.0f));
		m_camera.Update();
	}
	//シェーダーをロード。
	m_pEffect = CEngine::Instance().EffectManager().LoadEffect("../tkEngine/presetShader/ColorPrim.fx");

}
void CTestPrimitiveRender::Update()
{
}
void CTestPrimitiveRender::Render(tkEngine::CRenderContext& renderContext)
{
	//プリミティブを描画。
	const CMatrix& mMVP = m_camera.GetViewProjectionMatrix();
	m_pEffect->SetTechnique(renderContext, "ColorPrim");
	m_pEffect->SetValue(renderContext, "g_mWVP", &mMVP, sizeof(mMVP));
	m_pEffect->Begin(renderContext);
	m_pEffect->BeginPass(renderContext, 0);
	renderContext.SetVertexDeclaration(m_primitive.GetVertexDecl());
	renderContext.SetStreamSource(0,m_primitive.GetVertexBuffer());
	renderContext.SetIndices(m_primitive.GetIndexBuffer());
	renderContext.DrawIndexedPrimitive(&m_primitive);
	m_pEffect->EndPass(renderContext);
	m_pEffect->End(renderContext);
}