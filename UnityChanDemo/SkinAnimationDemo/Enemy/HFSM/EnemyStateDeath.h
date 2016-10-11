/*!
 * @brief	死亡状態。
 */

#pragma once 

#include "IEnemyState.h"

class EnemyStateDeath : public IEnemyState{
public:
	/*!
	 * @brief	コンストラクタ。
	 */
	EnemyStateDeath( Enemy* enemy );
	/*!
	 * @brief	デストラクタ。
	 */
	~EnemyStateDeath();
	void Update() override;
	void Enter() override;
	void Leave() override;
};