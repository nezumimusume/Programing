/*!
 *@brief	ゲームシーン。
 */

#include "stdafx.h"
#include "Scene/GameScene.h"

#include "Player/Player.h"
#include "UnityChanInstance.h"
#include "Car.h"
#include "Map/Map.h"
#include "Map/Sky.h"
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

CPhysicsWorld* g_physicsWorld = NULL;
Player* g_player = NULL;
CRandom g_random;
DamageCollisionWorld* g_damageCollisionWorld = NULL;
EnemyManager* g_enemyManager = NULL;
extern SAtmosphericScatteringParam g_testAtmos;

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
	DeleteGO(sky);
	//DeleteGO(g_car);
	DeleteGO(g_player);
	DeleteGO(g_enemyManager);
	//DeleteGO(unityChanInstance);
	DeleteGO(g_damageCollisionWorld);
	DeleteGO(g_camera);
	DeleteGO(&bgmSoundSource);
	DeleteGO(gameOver2D);
}
bool GameScene::Start()
{
	switch (initStep) {
	case InitStep_Load:	
		//unityChanInstance = NewGO<UnityChanInstance>(0);
		map = NewGO<Map>(0);
		ground = NewGO<Ground>(0);
		g_enemyManager = NewGO<EnemyManager>(0);
		playerHPBar = NewGO<PlayerHPBar>(0);
		playerMPBar = NewGO<PlayerMPBar>(0);
		g_damageCollisionWorld = NewGO<DamageCollisionWorld>(0);
		g_player = NewGO<Player>(0);
		sky = NewGO<Sky>(0);
		sky->SetPlayer(g_player);
		//g_car = NewGO<Car>(0);
		g_camera = NewGO<GameCamera>(0);
		g_player->SetPosition(CVector3(-10.0f, 4.5f, 0.0f));
		g_camera->SetPlayer(g_player);
		MotionBlur().SetCamera(&g_camera->GetCamera());

		bgmSoundSource.InitStreaming("Assets/sound/wind.wav");
		bgmSoundSource.Play(true);
		bgmSoundSource.SetVolume(0.5f);
		AddGO(0, &bgmSoundSource);
		
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
			&& sky->IsStart()
		) {
			//全て初期化完了。
			g_nowLoading->SetActiveFlag(false);
			return true;
		}
		break;
	}
	
	return false;
}
void GameScene::Update() 
{
	const float km = 0.0010f;
	const float ESun = 20.0f;
	const float kr = 0.0025f;
	switch (state) {
	case State_Play: {
		if (g_player->GetState() == Player::enState_Dead) {
			//プレイヤーが死んだ。
			gameOver2D = NewGO<GameOver2D>(0);
			state = State_Over;
		}
		//待機錯乱のテスト

		//惑星の半径。

		g_testAtmos.fKm4PI = km * 4.0f * CMath::PI;
		g_testAtmos.fKmESun = km * ESun;

		g_testAtmos.fKr4PI = kr * 4.0f * CMath::PI;
		g_testAtmos.fKrESun = kr * ESun;
		g_testAtmos.fOuterRadius = 50.0f;
		g_testAtmos.fOuterRadius2 = g_testAtmos.fOuterRadius * g_testAtmos.fOuterRadius;
		g_testAtmos.fInnerRadius = 1.0f;
		g_testAtmos.fInnerRadius2 = g_testAtmos.fInnerRadius * g_testAtmos.fInnerRadius;
		g_testAtmos.fScale = 1.0f / (g_testAtmos.fOuterRadius - g_testAtmos.fInnerRadius);
		g_testAtmos.fScaleDepth = 0.25f;
		g_testAtmos.fScaleOverScaleDepth = (1.0f / (g_testAtmos.fOuterRadius - g_testAtmos.fInnerRadius)) / g_testAtmos.fScaleDepth;
		g_testAtmos.g = -0.990f;
		g_testAtmos.g2 = g_testAtmos.g * g_testAtmos.g;

		float fWavelength[3], fWavelength4[3];
		fWavelength[0] = 0.650f;		// 650 nm for red
		fWavelength[1] = 0.570f;		// 570 nm for green
		fWavelength[2] = 0.475f;		// 475 nm for blue
		fWavelength4[0] = powf(fWavelength[0], 4.0f);
		fWavelength4[1] = powf(fWavelength[1], 4.0f);
		fWavelength4[2] = powf(fWavelength[2], 4.0f);
		g_testAtmos.v3InvWavelength.Set(1 / fWavelength4[0], 1 / fWavelength4[1], 1 / fWavelength4[2]);
		g_testAtmos.v3LightPos.Set(0.0f, 2000.0f, 2000.0f);
		g_testAtmos.v3LightDirection = g_testAtmos.v3LightPos;
		g_testAtmos.v3LightDirection.Scale(-1.0f);
		g_testAtmos.v3LightDirection.Normalize();
		g_testAtmos.fCameraHeight = g_camera->GetCamera().GetPosition().Length();
		g_testAtmos.fCameraHeight2 = g_testAtmos.fCameraHeight * g_testAtmos.fCameraHeight;

	}break;
	case State_Over:
		gameOverTimer += GameTime().GetFrameDeltaTime();
		if (gameOverTimer > 6.0f) {
			//死亡して2秒以上経過した。
			DeleteGO(this);
			g_nowLoading->SetActiveFlag(true);
			gameScene = NewGO<GameScene>(0);
		}
		break;
	}
}