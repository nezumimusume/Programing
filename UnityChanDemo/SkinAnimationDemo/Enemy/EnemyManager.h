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
	std::vector<Enemy*>& GetEnemyList()
	{
		return enemyList;
	}
	/*!
	* @brief	⊿タイムに乗算される値を設定。
	*@param[in]	mul		グローバル⊿タイムに乗算される値。この値に0.5を設定するとエネミーの挙動が0.5倍速になります。
	*/
	void SetFrameDeltaTimeMul(float mul);
private:
	std::vector<Enemy*>		enemyList;		//!<エネミーのリスト。
};