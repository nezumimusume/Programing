#pragma once

#include "tkEngine/camera/tkSpringCamera.h"

class Player;
class GameCamera : public IGameObject{
public:
	GameCamera()
	{
	}
	~GameCamera()
	{
	}
	void Update() override;
	bool Start() override;
private:
	Player*	m_player = nullptr;
	CVector3 m_toCameraPos = CVector3::Zero;
	CSpringCamera m_springCamera;
};