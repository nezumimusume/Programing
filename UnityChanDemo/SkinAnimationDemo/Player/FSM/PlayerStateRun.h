/*!
 * @brief	プレイヤーの走り状態クラス。
 */
#pragma once

#include "Player/FSM/IPlayerState.h"

class PlayerStateRun : public IPlayerState
{
public:
	PlayerStateRun(Player* player);
	~PlayerStateRun();
	void Update() override;
	void Enter() override;
	void Leave() override;
};

