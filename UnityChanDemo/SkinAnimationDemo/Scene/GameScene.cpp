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
	DeleteGO(sky);
	//DeleteGO(g_car);
	DeleteGO(g_player);
	DeleteGO(g_enemyManager);
	DeleteGO(unityChanInstance);
	DeleteGO(g_damageCollisionWorld);
	DeleteGO(g_camera);
	DeleteGO(&bgmSoundSource);
}
bool GameScene::Start()
{
	switch (initStep) {
	case InitStep_Load:	
		unityChanInstance = NewGO<UnityChanInstance>(0);
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
			return true;
		}
		break;
	}
	
	return false;
}
void GameScene::Update() 
{
	if (Pad(0).IsTrigger(enButtonStart)) {
		DeleteGO(this);
	}
}