#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

void GameCamera::Update() 
{
	//カメラを回転させる。
	float rStick_x = Pad(0).GetRStickXF();
	float rStick_y = Pad(0).GetRStickYF();

	if (fabsf(rStick_x) > 0.0f) {
		//Y軸周りの回転を計算。
		//回す
		CMatrix mRot;
		mRot.MakeRotationY(0.05f * rStick_x);
		mRot.Mul(m_toCameraPos);
	}
	if (fabsf(rStick_y) > 0.0f) {
		CVector3 rotAxis;
		rotAxis.Cross(CVector3::Up, m_toCameraPos);
		rotAxis.Normalize();
		CMatrix mRot;
		mRot.MakeRotationAxis(rotAxis, 0.05f * rStick_y);
		CVector3 toPositionOld = m_toCameraPos;
		mRot.Mul(m_toCameraPos);
		CVector3 toPosDir = m_toCameraPos;
		toPosDir.Normalize();
		if (toPosDir.y < -0.5f) {
			//カメラが上向きすぎ。
			m_toCameraPos = toPositionOld;
		}
		else if (toPosDir.y > 0.8f) {
			//カメラが下向きすぎ。
			m_toCameraPos = toPositionOld;
		}
	}

	CVector3 target = m_player->GetPosition();
	target.y += 40.0f;
	CVector3 pos;
	pos.Add(target, m_toCameraPos);

	m_springCamera.SetTarPosition(pos);
	m_springCamera.SetTarTarget(target);

	m_springCamera.Update();
}
bool GameCamera::Start()
{
	m_player = FindGO<Player>("Player");
	CCamera& camera = MainCamera();
	
	m_springCamera.Init(&camera, 1000.0f, true, 5.0f);

	CVector3 target = m_player->GetPosition();
	target.y += 40.0f;
	m_toCameraPos.Set(0.0f, 20.0f, 150.0f);
	CVector3 pos;
	pos.Add(target, m_toCameraPos);

	m_springCamera.SetTarPosition(pos);
	m_springCamera.SetPosition(pos);
	m_springCamera.SetTarget(target);
	m_springCamera.SetTarTarget(target);
	m_springCamera.SetFar(1000.0f);
	m_springCamera.SetNear(1.0f);
	m_springCamera.SetDampingRate(1.2f);

	return true;
}