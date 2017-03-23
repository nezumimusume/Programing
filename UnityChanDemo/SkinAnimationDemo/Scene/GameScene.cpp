/*!
 *@brief	ゲームシーン。
 */

#include "stdafx.h"
#include "Scene/GameScene.h"

#include "Player/Player.h"
#include "UnityChanInstance.h"
#include "Car.h"
#include "Map/Map.h"

#include "Map/Ground.h"
#include "tkEngine/Physics/tkPhysics.h"
#include "EnemyTest.h"
#include "Enemy/EnemyManager.h"
#include <time.h>
#include "DamageCollisionWorld.h"
#include "tkEngine/graphics/sprite/tkSprite.h"
#include "HUD/PlayerHPBar.h"
#include "HUD/PlayerMPBar.h"
#include "HUD/NowLoading.h"
#include "HUD/GameOver2D.h"
#include "tkEngine/graphics/tkAtmosphericScatteringParam.h"
#include "ScreenEffect/Fade.h"
#include "HUD/MagicSkill2D.h"

CPhysicsWorld* g_physicsWorld = NULL;
Player* g_player = NULL;
CRandom g_random;
DamageCollisionWorld* g_damageCollisionWorld = NULL;
EnemyManager* g_enemyManager = NULL;



GameScene::GameScene()
{
}
GameScene::~GameScene()
{
}
void GameScene::OnDestroy()
{
	DeleteGO(map);
	DeleteGO(ground);
	DeleteGO(playerHPBar);
	DeleteGO(playerMPBar);
	//DeleteGO(g_car);
	DeleteGO(g_player);
	DeleteGO(g_enemyManager);
	//DeleteGO(unityChanInstance);
	DeleteGO(g_damageCollisionWorld);
	DeleteGO(g_camera);
	DeleteGO(&bgmSoundSource);
	DeleteGO(gameOver2D);
	DeleteGO(&inGameLight);
	DeleteGO(magicSkill2D);
}
bool GameScene::Start()
{
	switch (initStep) {
	case InitStep_Load:	
		
		//完全にモデルデータを開放する。
		//SkinModelDataResources().Release();
		
		g_fade->StartFadeIn();
		AddGO(0, &inGameLight);
		map = NewGO<Map>(0);
		ground = NewGO<Ground>(0);
		g_enemyManager = NewGO<EnemyManager>(0);
		playerHPBar = NewGO<PlayerHPBar>(0);
		playerMPBar = NewGO<PlayerMPBar>(0);
		magicSkill2D = NewGO<MagicSkill2D>(0);
		g_damageCollisionWorld = NewGO<DamageCollisionWorld>(0);
		g_player = NewGO<Player>(0);
		g_camera = NewGO<GameCamera>(0);
		g_player->SetPosition(CVector3(-10.0f, 4.5f, 0.0f));
		//g_player->SetPosition(CVector3(0.0f, 0.5f, 177.0));
		g_camera->SetPlayer(g_player);
		MotionBlur().SetCamera(&g_camera->GetCamera());
		MotionBlur().SetEnable(false);
		bgmSoundSource.InitStreaming("Assets/sound/wind.wav");
		bgmSoundSource.SetTags(enGameObjectTags_BGM);
		bgmSoundSource.Play(true);
		bgmSoundSource.SetVolume(0.5f);
		AddGO(0, &bgmSoundSource);

		Sky().SetEnable(&g_camera->GetCamera(), &inGameLight.GetDefaultLight());
		itemModelData.LoadModelDataAsync("Assets/modelData/Apple.X", NULL);
		initStep = InitStep_WaitLoad;
		break;
	case InitStep_WaitLoad:
		if (g_player->IsStart()
			&& g_enemyManager->IsStart()
			&& map->IsStart()
			&& ground->IsStart()
			&& playerHPBar->IsStart()
			&& playerMPBar->IsStart()
			&& playerMPBar->IsStart()
			&& itemModelData.IsLoadEnd()
			&& !g_fade->IsExecute()
		) {
			//全て初期化完了。
			g_nowLoading->SetActiveFlag(false);
			Tonemap().Reset();
			return true;
		}
		break;
	}
	
	return false;
}
void GameScene::Update() 
{
	
	switch (state) {
	case State_Play: {
		if (g_player->GetState() == Player::enState_Dead) {
			//プレイヤーが死んだ。
			gameOver2D = NewGO<GameOver2D>(0);
			state = State_Over;
		}
		//CalcMieAndRayleighColors(mieColor, rayColor, posToCameraDir, {0.0f, 0.0f, 0.0f});
	}break;
	case State_Over:
		gameOverTimer += GameTime().GetFrameDeltaTime();
		if (gameOverTimer > 6.0f) {
			//死亡して2秒以上経過した。
			g_fade->StartFadeOut();
			state = State_WaitFadeOut;
		}
		break;
	case State_WaitFadeOut:
		if (!g_fade->IsExecute()) {
			DeleteGO(this);
			g_nowLoading->SetActiveFlag(true);
			gameScene = NewGO<GameScene>(0);
		}
		break;
	}
}