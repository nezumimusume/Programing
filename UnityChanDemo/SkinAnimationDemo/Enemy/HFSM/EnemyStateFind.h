/*!
 * @brief	発見状態。
 */

#pragma once

#include "IEnemyState.h"

/*!
 * @brief	索敵状態。
 */
class EnemyStateFind : public IEnemyState{
private:

	enum EnLocalState{
		enLocalState_Run,
		enLocalState_Attack,
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
};