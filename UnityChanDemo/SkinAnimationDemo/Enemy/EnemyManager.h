/*!
 * @brief	エネミーマネージャ。
 */

#pragma once


class Enemy;

/*!
 * @brief	敵さんのマネージャー。
 *@details
 * Facadeパターン。
 */
class EnemyManager : public IGameObject{
public:
	EnemyManager();
	~EnemyManager();
	bool Start() override;
	void Update() override;
	void Render(CRenderContext& renderContext) override;
	const std::vector<Enemy*>& GetEnemyList() const
	{
		return enemyList;
	}
private:
	std::vector<Enemy*>		enemyList;		//!<エネミーのリスト。
};