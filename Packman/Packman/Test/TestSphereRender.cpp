/*!
 *@brief	球体の描画テスト。
 */

#include "stdafx.h"
#include "TestSphereRender.h"
#include "tkEngine/graphics/tkEffect.h"
#include "tkEngine/graphics/tkLight.h"

using namespace tkEngine;

void CTestSphereRender::Start()
{
	m_sphere.Create( 10.0f, 10, 0x8844FFF, true );
	m_pEffect = CEngine::Instance().EffectManager().LoadEffect("Assets/presetShader/ColorNormalPrim.fx");
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
	CVector3 lightDir;
	/*m_light.SetDiffuseLightColor(0, CVector4(0.6f, 0.6f, 0.6f, 1.0f));
	lightDir = CVector3::AxisY;
	m_light.SetDiffuseLightDirection(0, lightDir);
	
	m_light.SetDiffuseLightColor(1, CVector4(5.6f, 0.6f, 0.6f, 1.0f));
	lightDir = CVector3::AxisX;
	lightDir.Scale(-1.0f);
	m_light.SetDiffuseLightDirection(1, lightDir);

	m_light.SetDiffuseLightColor(2, CVector4(10.6f, 0.6f, 0.6f, 1.0f));
	lightDir.Add( CVector3::AxisX, CVector3::AxisZ);
	lightDir.Normalize();
	m_light.SetDiffuseLightDirection(2, lightDir);

	m_light.SetDiffuseLightColor(3, CVector4(1.0f, 1.0f, 0.6f, 1.0f));
	lightDir = CVector3::AxisY;
	lightDir.Scale(-1.0f);
	lightDir.Normalize();
	m_light.SetDiffuseLightDirection(3, lightDir);*/

	m_light.SetAmbinetLight(CVector3(10.0f, 0.5f, 0.0f));
	m_idMapModel.Create(m_sphere.GetPrimitive());
}
void CTestSphereRender::Update()
{
	m_angle += CMath::PI / 360.0f;
	CQuaternion rot;
	CVector3 pos;
	pos.Set(-10.0f, 0.0f, 0.0f);
	rot.SetRotation(CVector3::AxisX, m_angle);
	m_sphere.SetRotation(rot);
	m_sphere.SetPosition(pos);
	m_sphere.UpdateWorldMatrix();

	CMatrix mMVP = m_camera.GetViewProjectionMatrix();
	const CMatrix& mWorld = m_sphere.GetWorldMatrix();

	mMVP.Mul(mWorld, mMVP);
	m_idMapModel.SetWVPMatrix(mMVP);
//	tkEngine::CEngine::Instance().IDMap().Entry(&m_idMapModel);
}
void CTestSphereRender::Render(tkEngine::CRenderContext& renderContext)
{
	CMatrix mMVP = m_camera.GetViewProjectionMatrix();
	const CMatrix& mWorld = m_sphere.GetWorldMatrix();

	mMVP.Mul(mWorld, mMVP);
	CMatrix mRot = m_sphere.GetRotationMatrix();
	m_pEffect->SetTechnique(renderContext, "ColorNormalPrimIuminance");
	m_pEffect->Begin(renderContext);
	m_pEffect->BeginPass(renderContext, 0);
	m_pEffect->SetValue(renderContext, "g_mWVP", &mMVP, sizeof(mMVP));
	m_pEffect->SetValue(renderContext, "g_worldRotationMatrix", &mRot, sizeof(mRot));
	m_pEffect->SetValue(
		renderContext, 
		"g_light", 
		&m_light,
		sizeof(m_light)
	);
	
	m_pEffect->CommitChanges(renderContext);
	m_sphere.Render(renderContext);

	m_pEffect->EndPass(renderContext);
	m_pEffect->End(renderContext);
}
