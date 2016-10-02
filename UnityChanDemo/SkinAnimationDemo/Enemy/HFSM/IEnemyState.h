/*!
 * @brief	敵の状態の基底クラス。
 */

#pragma once

/*!
 * @brief	敵の状態の基底クラス。
 */
class IEnemyState{
public:
	IEnemyState()
	{
	}
	virtual ~IEnemyState()
	{
	}
	virtual void Update() = 0;
	virtual void Enter() = 0;
	virtual void Leave() = 0;
protected:
	std::vector<IEnemyState*>	m_childState;		//子供。

};