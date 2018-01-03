/*!
 * @brief	プレイヤーの移動処理。
 */

#pragma once

#include "tkEngine/character/tkCharacterController.h"

class CPlayer;
class CGameCamera;

class CPlayerMove : public IGameObject{
public:
	CPlayerMove( CPlayer* pl );
	~CPlayerMove();
	bool Start() override final;
	void Update() override final;
	/*!
	 *@brief	移動速度の取得。
	 */
	CVector3 GetMoveSpeed() const
	{
		return m_moveSpeed;
	}
private:
	CCharacterController m_charaCon;		//キャラクターコントローラ。
	CPlayer* m_player = nullptr;
	CVector3 m_moveSpeed = CVector3::Zero;	//移動速度。
	CGameCamera* m_gameCamera = nullptr;
	float m_accelTime = 0.0f;
};