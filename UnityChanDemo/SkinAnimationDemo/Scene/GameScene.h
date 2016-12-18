/*!
 *@brief	ゲームシーン。
 */

#pragma once

#include "tkEngine/Sound/tkSoundSource.h"

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
	bool Start() override;
	void Update() override;
private:
	enum InitStep {
		InitStep_Load,
		InitStep_WaitLoad,
	};
	Map*				map = NULL;
	Ground*				ground = NULL;
	PlayerHPBar*		playerHPBar = NULL;
	PlayerMPBar*		playerMPBar = NULL;
	Sky* 				sky = NULL;
	UnityChanInstance*	unityChanInstance = NULL;
	CSoundSource		bgmSoundSource;
	InitStep			initStep = InitStep_Load;
};