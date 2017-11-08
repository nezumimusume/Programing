#pragma once

#include "Player.h"
#include "tkEngine/camera/tkSpringCamera.h"

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	void NotifyGameOver();
	void NotifyRestart();
	void NotifyGameClear();
private:
	Player* m_player;	//プレイヤー。
	CSpringCamera m_springCamera;	//!<バネカメラ。
};

