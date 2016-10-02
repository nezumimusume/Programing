/*!
 * @brief	歩き状態。
 */

#pragma once

#include "IEnemyState.h"

/*!
 * @brief	歩き状態。
 */
class EnemyStateWalk : public IEnemyState{
public:
	/*!
	 * @brief	コンストラクタ。
	 */
	EnemyStateWalk();
	/*!
	 * @brief	デストラクタ。
	 */
	~EnemyStateWalk();
	void Update() override;
	void Enter() override;
	void Leave() override;
};