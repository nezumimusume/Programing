/*!
 * @brief	カメラ。
 */
#include "stdafx.h"
#include "Packman/game/CCamera.h"
#include "Packman/game/CGameManager.h"

CGameCamera::CGameCamera()
{
}
CGameCamera::~CGameCamera()
{
}	
void CGameCamera::Start()
{
	CVector3 cameraTarget;
	m_playerDist.Set(0.0f, 3.5f, -0.1f);
	cameraTarget = m_playerDist;
	cameraTarget.z = 0.0f;
	m_camera.SetPosition(m_playerDist);
	m_camera.SetTarget(CVector3::Zero);
	m_camera.SetUp(CVector3::Up);
	m_camera.SetFar(100000.0f);
	m_camera.SetNear(0.1f);
	m_camera.SetViewAngle(CMath::DegToRad(45.0f));
	m_camera.Update();
}
void CGameCamera::Update()
{
	//プレイヤーに追従。
	//バネカメラにしようかなぁ・・・。
	CVector3 target = Player().GetPosition();
	m_camera.SetTarget(target);
	CVector3 cameraPos;
	cameraPos.Add(target, m_playerDist);
	m_camera.SetPosition(cameraPos);
	m_camera.Update();
}
void CGameCamera::Render(tkEngine::CRenderContext& renderContext)
{
}