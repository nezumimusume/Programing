/*!
 *@brief	ゲームカメラ
 */

#pragma once

#include "tkEngine/camera/tkSpringCamera.h"

class Player;
class Car;
/*!
 *@brief	ゲームカメラ。
 */
class GameCamera : public IGameObject{
public:
	GameCamera();
	~GameCamera();
	void Start() override ;
	void Update() override ;
	void Render( CRenderContext& renderContext ) override;
	void SetPlayer(Player* player)
	{
		this->player = player;
	}
	void SetCar(Car* car)
	{
		this->car = car;
	}
	const CCamera& GetCamera() const
	{
		return *springCamera.GetCamera();
	}
private:
	//CCamera camera;
	CSpringCamera springCamera;
	Car* car;
	Player*	player;
	CVector3	toPosition;		//注視点から視点へのベクトル。
};


extern GameCamera*			g_camera;				//カメラ。