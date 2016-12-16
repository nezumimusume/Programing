/*!
 *@brief	ゲームシーン。
 */

#pragma once

class Map;
class Ground;
class PlayerHPBar;
class PlayerMPBar;
class Sky;
class UnityChanInstance;

class GameScene : public IGameObject{
public:
	/*!
	 *@brief	コンストラクタ。
	 */
	GameScene();
	/*!
	 *@brief	デストラクタ。
	 */
	~GameScene();
	void OnDestroy() override;
	void Start() override;
	void Update() override;
private:
	Map*				map = NULL;
	Ground*				ground = NULL;
	PlayerHPBar*		playerHPBar = NULL;
	PlayerMPBar*		playerMPBar = NULL;
	Sky* 				sky = NULL;
	UnityChanInstance*	unityChanInstance = NULL;
};