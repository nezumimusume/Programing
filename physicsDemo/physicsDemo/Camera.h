#pragma once

#include "tkEngine/graphics/tkCamera.h"

class CPlayer;
//プレイヤー追従カメラ。
class CGameCamera : public IGameObject{
public:
	CGameCamera()
	{
		m_player = nullptr;
	}
	virtual void Start();
	virtual void Update();
	virtual void Render(CRenderContext& renderContext);
	void SetPlayer(CPlayer* pl)
	{
		m_player = pl;
	}
	CCamera* GetCamera()
	{
		return &m_camera;
	}
private:
	CPlayer*	m_player;
	CCamera		m_camera;
	CVector3	m_distToPlayer;
};