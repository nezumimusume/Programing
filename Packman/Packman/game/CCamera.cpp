/*!
 * @brief	ÉJÉÅÉâÅB
 */
#include "stdafx.h"
#include "Packman/game/CCamera.h"


CGameCamera::CGameCamera()
{
}
CGameCamera::~CGameCamera()
{
}	
void CGameCamera::Start()
{
	CVector3 cameraPos;
	CVector3 cameraTarget;
	cameraPos.Set(0.0f, 2.0f, -1.0f);
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
void CGameCamera::Update()
{
	m_camera.Update();
}
void CGameCamera::Render(tkEngine::CRenderContext& renderContext)
{
}