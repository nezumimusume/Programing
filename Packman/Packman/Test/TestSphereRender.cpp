/*!
 *@brief	球体の描画テスト。
 */

#include "stdafx.h"
#include "TestSphereRender.h"
#include "tkEngine/graphics/tkEffect.h"

using namespace tkEngine;

void CTestSphereRender::Start()
{
	m_sphere.Create( 10.0f, 100, 0xFFF00FFF, false );
	m_pEffect = CEngine::Instance().EffectManager().LoadEffect("../tkEngine/presetShader/ColorPrim.fx");
	//カメラを初期化。
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
void CTestSphereRender::Update()
{
	m_angle += CMath::PI / 360.0f;
	CQuaternion rot;
	CVector3 pos;
	pos.Set(-10.0f, 0.0f, 0.0f);
	rot.SetRotation(CVector3::AxisY, m_angle);
	m_sphere.SetRotation(rot);
	m_sphere.SetPosition(pos);
	m_sphere.UpdateWorldMatrix();
}
void CTestSphereRender::Render(tkEngine::CRenderContext& renderContext)
{
	CMatrix mMVP = m_camera.GetViewProjectionMatrix();
	const CMatrix& mWorld = m_sphere.GetWorldMatrix();

	mMVP.Mul(mWorld, mMVP);
	mMVP.Transpose();
	m_pEffect->SetTechnique(renderContext, "ColorPrim");
	m_pEffect->SetValue(renderContext, "g_mWVP", &mMVP, sizeof(mMVP));
	m_pEffect->Begin(renderContext);
	m_pEffect->BeginPass(renderContext, 0);

	m_sphere.Render(renderContext);

	m_pEffect->EndPass(renderContext);
	m_pEffect->End(renderContext);
}
