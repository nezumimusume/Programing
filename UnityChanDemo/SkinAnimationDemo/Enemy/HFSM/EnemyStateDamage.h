/*!
 * @brief	ヤラレ状態。
 */

#pragma once 

#include "IEnemyState.h"

class EnemyStateDamage : public IEnemyState{
public:
	/*!
	 * @brief	コンストラクタ。
	 */
	EnemyStateDamage( Enemy* enemy );
	/*!
	 * @brief	デストラクタ。
	 */
	~EnemyStateDamage();
	void Update() override;
	void Enter() override;
	void Leave() override;
};