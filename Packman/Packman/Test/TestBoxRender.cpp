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
	m_box.Create(CVector3(20.0f, 20.0f, 20.0f), 0xFFF00FFF, true);
	m_pEffect = CEngine::Instance().EffectManager().LoadEffect("../tkEngine/presetShader/ColorNormalPrim.fx");
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
	//ライトを初期化。
	{
		CVector3 lightDir;
		m_light.SetDiffuseLightColor(0, CVector4(0.2f, 0.2f, 0.2f, 1.0f));
		lightDir = CVector3::AxisY;
		m_light.SetDiffuseLightDirection(0, lightDir);

		m_light.SetDiffuseLightColor(1, CVector4(0.4f, 0.2f, 0.2f, 1.0f));
		lightDir = CVector3::AxisX;
		lightDir.Scale(-1.0f);
		m_light.SetDiffuseLightDirection(1, lightDir);

		m_light.SetDiffuseLightColor(2, CVector4(0.4f, 0.3f, 0.3f, 1.0f));
		lightDir.Add(CVector3::AxisX, CVector3::AxisZ);
		lightDir.Normalize();
		m_light.SetDiffuseLightDirection(2, lightDir);
	}
}
void CTestBoxRender::Update() 
{
	m_angle += CMath::PI / 360.0f;
	CQuaternion rot;
	CVector3 pos;
	pos.Set(10.0f, 0.0f, 0.0f);
	rot.SetRotation(CVector3::AxisX, m_angle);
	m_box.SetRotation(rot);
	m_box.SetPosition(pos);
	m_box.UpdateWorldMatrix();
}
void CTestBoxRender::Render(tkEngine::CRenderContext& renderContext) 
{
	CMatrix mMVP = m_camera.GetViewProjectionMatrix();
	const CMatrix& mWorld = m_box.GetWorldMatrix();

	mMVP.Mul(mWorld, mMVP);
	mMVP.Transpose();
	CMatrix mRot = m_box.GetRotationMatrix();
	mRot.Transpose();
	m_pEffect->SetTechnique(renderContext, "ColorNormalPrim");
	m_pEffect->SetValue(renderContext, "g_mWVP", &mMVP, sizeof(mMVP));
	m_pEffect->SetValue(renderContext, "g_worldRotationMatrix", &mRot, sizeof(mRot));
	m_pEffect->SetValue(
		renderContext,
		"g_light",
		&m_light,
		sizeof(m_light)
		);
	m_pEffect->Begin(renderContext);
	m_pEffect->BeginPass(renderContext, 0);

	m_box.Render(renderContext);

	m_pEffect->EndPass(renderContext);
	m_pEffect->End(renderContext);
}