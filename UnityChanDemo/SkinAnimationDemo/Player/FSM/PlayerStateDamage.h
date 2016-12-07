/*!
 * @brief	プレイヤーのやられ状態クラス。
 */
#pragma once

#include "Player/FSM/IPlayerState.h"

class PlayerStateDamage : public IPlayerState
{
public:
	PlayerStateDamage(Player* player);
	~PlayerStateDamage();
	void Update() override;
	void Enter() override;
	void Leave() override;
	bool IsPossibleDamage() const override
	{
		return false;
	}
	bool IsPossibleLockOn() const override
	{
		return true;
	}
};

