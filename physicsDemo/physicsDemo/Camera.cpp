#include "stdafx.h"
#include "Camera.h"
#include "Player.h"
void CGameCamera::Start()
{
	m_distToPlayer.Set(0.0f, 1.0f, -1.5f);
}
void CGameCamera::Update()
{
	CVector3 p = m_player->GetPosition();
	m_camera.SetTarget(p);
	p.Add(m_distToPlayer);
	m_camera.SetPosition(p);
	m_camera.Update();
}
void CGameCamera::Render(CRenderContext& renderContext)
{

}