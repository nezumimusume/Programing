/*!
 * @brief	攻撃状態。
 */

#pragma once

#include "IEnemyState.h"

class EnemyStateAttack : public IEnemyState{
public:
	/*!
	 * @brief	コンストラクタ。
	 */
	EnemyStateAttack( Enemy* enemy );
	/*!
	 * @brief	デストラクタ。
	 */
	~EnemyStateAttack();
	void Update() override;
	void Enter() override;
	void Leave() override;
};