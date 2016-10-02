/*!
 * @brief	発見状態。
 */

#pragma once

#include "UnityChan.h"
#include "IEnemyState.h"

/*!
 * @brief	索敵状態。
 */
class EnemyStateFind : public IEnemyState{
private:

	enum EnLocalState{
		enLocalState_Run,
		enLocalState_Attack,
		enLocalState_Idle,
	};
public:
	/*!
	 * @brief	コンストラクタ。
	 */
	EnemyStateFind(Enemy* enemy);
	/*!
	 * @brief	デストラクタ。
	 */
	~EnemyStateFind();
	void Update() override;
	void Enter() override;
	void Leave() override;
private:
	float timer;
	UnityChan::SBattleSeat*		battleSeat;
};