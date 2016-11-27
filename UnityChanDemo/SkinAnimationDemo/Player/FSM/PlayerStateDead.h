/*!
 * @brief	プレイヤーの死亡状態クラス。
 */
#pragma once

#include "Player/FSM/IPlayerState.h"


class PlayerStateDead : public IPlayerState
{
public:
	PlayerStateDead(Player* player);
	~PlayerStateDead();
	void Update() override;
	void Enter() override;
	void Leave() override;
	bool IsPossibleDamage() const override
	{
		return false;
	}
private:
	float timer = 0.0f;
};

