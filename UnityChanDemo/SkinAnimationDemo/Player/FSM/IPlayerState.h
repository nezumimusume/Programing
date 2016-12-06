/*!
 * @brief	プレイヤーのステートクラス。
 */

#pragma once

class Player;
/*!
 * @brief	プレイヤーのステートクラス。
 */
class IPlayerState{
public:
	IPlayerState( Player* player )
	{
		this->player = player;
	}
	virtual ~ IPlayerState()
	{
	}
	virtual void Update() = 0;
	virtual void Enter() = 0;
	virtual void Leave() = 0;
	//ダメージを受けることが出来るか判定。
	virtual bool IsPossibleDamage() const
	{
		return true;
	}
	//ロックオンが可能？
	virtual bool IsPossibleLockOn() const
	{
		return false;
	}
protected:
	Player* player;		//プレイヤー。
};
