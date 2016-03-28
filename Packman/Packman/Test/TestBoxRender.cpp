/*!
 *@brief	ボックスの描画テスト。
 */

#include "stdafx.h"
#include "test/TestBoxRender.h"
#include "tkEngine/graphics/tkEffect.h"

using namespace tkEngine;

void CTestBoxRender::Start()
{
	m_angle = 0;
	m_box.Create(CVector3(20.0f, 20.0f, 20.0f), 0xFFFFFFFF);
	m_pEffect = CEngine::Instance().EffectManager().LoadEffect("../tkEngine/presetShader/ColorPrim.fx");
	//カメラを初期化
	{
		CVector3 cameraPos;
		CVector3 cameraTarget;
		cameraPos.Set(0.0f, 0.0f, -100.0f);
		cameraTarget = cameraPos;
		cameraTarget.z = 0.0f;
		m_camera.SetPosition(cameraPos);
		m_camera.SetTarget(CVector3::Zero);
		m_camera.SetUp(CVector3::Up);
		m_camera.SetFar(100000.0f);
		m_camera.SetNear(0.1f);
		m_camera.SetViewAngle(CMath::DegToRad(45.0f));
		m_camera.Update();
	}
}
void CTestBoxRender::Update() 
{
	m_angle += CMath::PI / 360.0f;
	CQuaternion rot;
	rot.SetRotation(CVector3::Up, m_angle);
	m_box.SetRotation(rot);
	m_box.UpdateWorldMatrix();
}
void CTestBoxRender::Render(tkEngine::CRenderContext& renderContext) 
{
	CMatrix mMVP = m_camera.GetViewProjectionMatrix();
	const CMatrix& mWorld = m_box.GetWorldMatrix();
	mMVP.Mul(mWorld, mMVP);
	m_pEffect->SetTechnique(renderContext, "ColorPrim");
	m_pEffect->SetValue(renderContext, "g_mWVP", &mMVP, sizeof(mMVP));
	m_pEffect->Begin(renderContext);
	m_pEffect->BeginPass(renderContext, 0);
	CPrimitive* prim = m_box.GetPrimitive();
	renderContext.SetRenderCommand(CRenderCommand_SetFVF(prim->GetVertexFormat()));
	renderContext.SetRenderCommand(CRenderCommand_SetStreamSource(
		0,
		prim->GetVertexBuffer()
	));
	renderContext.SetRenderCommand(CRenderCommand_SetIndices(
		prim->GetIndexBuffer()
	));
	renderContext.SetRenderCommand(CRenderCommand_DrawIndexedPrimitive(
		prim
	));
	m_pEffect->EndPass(renderContext);
	m_pEffect->End(renderContext);
}