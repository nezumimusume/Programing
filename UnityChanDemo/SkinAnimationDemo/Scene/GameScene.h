/*!
 *@brief	ゲームシーン。
 */

#pragma once

#include "tkEngine/Sound/tkSoundSource.h"
#include "Light/InGameLight.h"

class Map;
class Ground;
class PlayerHPBar;
class PlayerMPBar;

class UnityChanInstance;
class GameOver2D;
class MagicSkill2D;

class GameScene : public IGameObject{
public:
	//ゲームオブジェクトのタグ。
	enum EnGameObjectTags {
		enGameObjectTags_BGM = 1,				//!<BGM
		enGameObjectTags_EnemySound = 1 << 1,	//!<エネミーサウンド。
	};
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
	
	//デフォルトライトの取得。
	CLight& GetDefaultLight()
	{
		return inGameLight.GetDefaultLight();
	}
	CSkinModelData* GetItemModelData()
	{
		if (itemModelData.IsLoadEnd())
		{
			return itemModelData.GetBody();
		}
		else
		{
			return nullptr;
		}
	}
private:
	enum InitStep {
		InitStep_Load,
		InitStep_WaitLoad,
	};
	enum State {
		State_Play,	//ゲームプレイ中。
		State_Over,	//ゲームオーバー。
		State_WaitFadeOut,	//フェードアウト待ち。
	};
	Map*				map = NULL;
	Ground*				ground = NULL;
	PlayerHPBar*		playerHPBar = NULL;
	PlayerMPBar*		playerMPBar = NULL;
	UnityChanInstance*	unityChanInstance = NULL;
	CSoundSource		bgmSoundSource;
	InitStep			initStep = InitStep_Load;
	State				state = State_Play;
	float				gameOverTimer = 0.0f;
	GameOver2D*			gameOver2D = NULL;
	MagicSkill2D*		magicSkill2D = NULL;
	InGameLight			inGameLight;		//インゲームライト。
	CSkinModelDataHandle itemModelData;
};

extern GameScene* gameScene;