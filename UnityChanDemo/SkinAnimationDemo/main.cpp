#include "stdafx.h"

#include "Player/Player.h"
#include "UnityChanInstance.h"
#include "Car.h"
#include "Map/Map.h"
#include "Map/Sky.h"
#include "Map/Ground.h"
#include "Physics/Physics.h"
#include "EnemyTest.h"
#include "Enemy/EnemyManager.h"
#include <time.h>
#include "DamageCollisionWorld.h"
#include "tkEngine/Sound/tkSoundSource.h"
PhysicsWorld* g_physicsWorld = NULL;
Player* g_player = NULL;
CRandom g_random;
DamageCollisionWorld* g_damageCollisionWorld = NULL;
//#define MEMORY_LEAK_TEST		//定義でメモリリークテストが有効になる。
//#define PLAY_WAVE_FILE_TEST		//定義で波形データの再生テストが有効になる。
#ifdef PLAY_WAVE_FILE_TEST
class PlayWaveFileTest : public IGameObject {
	/*CWaveFile waveFile;
	char* buffer;*/
	CSoundSource soundSource;
public:
	PlayWaveFileTest() 
	{
	}
	~PlayWaveFileTest()
	{
	}
	void Start() override
	{
		//サウンドソースを初期化。
		soundSource.InitStreaming("Assets/sound/SoundTest.wav");
		//soundSource.Init("Assets/sound/MusicMono.wav");
		soundSource.Play(false);
		AddGO(0, &soundSource);
	}
	void Update() override
	{
	}
	void Render(CRenderContext& renderContext) override
	{
	}
};
#endif
#ifdef MEMORY_LEAK_TEST
//メモリリークテスト。
class MemoryLeakTest : public IGameObject {
	
public:
	MemoryLeakTest()
	{

	}
	void Start() override
	{

	}
	void Update() override
	{
		//スキンなしモデル。
		CSkinModelDataHandle nonSkinModelData;		//スキンモデルデータ。
		SkinModelDataResources().Load(nonSkinModelData, "Assets/modelData/Court.X", NULL);
		
		//スキンなしインスタンシングモデル。
		CSkinModelDataHandle nonSkinModelInstancing;
		SkinModelDataResources().Load(nonSkinModelInstancing, "Assets/modelData/Court.X", NULL, true, 10);
		
		//スキンありモデル。
		CSkinModelDataHandle skinModelData;
		SkinModelDataResources().Load(skinModelData, "Assets/modelData/Unity.X", NULL);
		//スキンありインスタンシングモデル。
		CSkinModelDataHandle skinModelInstancing;
		SkinModelDataResources().Load(skinModelInstancing, "Assets/modelData/Unity.X", NULL, true, 10);
	}
	void Render(CRenderContext& renderContext) override
	{

	}
};
#endif


/*!
 * @brief	tkEngineの初期化。
 */
void InitTkEngine( HINSTANCE hInst )
{
	SInitParam initParam;
	memset(&initParam, 0, sizeof(initParam));
	//コマンドバッファのサイズのテーブル。
	int commandBufferSizeTbl[] = {
		10 * 1024 * 1024,		//10MB
	};
	initParam.hInstance = hInst;
	initParam.gameObjectPrioMax = 255;
	initParam.numRenderContext = 1;	//レンダリングコンテキストは一本
	initParam.commandBufferSizeTbl = commandBufferSizeTbl;
	initParam.screenHeight = 720;
	initParam.screenWidth = 1280;
	initParam.frameBufferHeight = 720;
	initParam.frameBufferWidth = 1280;
	//Bloom
	initParam.graphicsConfig.bloomConfig.isEnable = true;
	initParam.graphicsConfig.edgeRenderConfig.isEnable = false;
	initParam.graphicsConfig.edgeRenderConfig.idMapWidth = initParam.frameBufferWidth;
	initParam.graphicsConfig.edgeRenderConfig.idMapHeight = initParam.frameBufferHeight;
	//Shadow
	initParam.graphicsConfig.shadowRenderConfig.Init();
	initParam.graphicsConfig.shadowRenderConfig.isEnable = true;
	initParam.graphicsConfig.shadowRenderConfig.shadowMapWidth = 1024;
	initParam.graphicsConfig.shadowRenderConfig.shadowMapHeight = 1024;
	initParam.graphicsConfig.shadowRenderConfig.numShadowMap = 3;
	
	//reflection
	initParam.graphicsConfig.reflectionMapConfig.isEnable = false;
	initParam.graphicsConfig.reflectionMapConfig.reflectionMapWidth = 512;
	initParam.graphicsConfig.reflectionMapConfig.reflectionMapHeight = 512;
	//DOF
	initParam.graphicsConfig.dofConfig.isEnable = true;
	//AA
	initParam.graphicsConfig.aaConfig.isEnable = true;

	Engine().Init(initParam);	//初期化。
	
	ShadowMap().SetNear(2.0f);
	ShadowMap().SetFar(40.0f);
	
}

int WINAPI wWinMain(
	HINSTANCE hInst,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow
	)
{
	//tkEngineの初期化。
	InitTkEngine( hInst );
	g_random.Init((unsigned long)time(NULL));
#ifdef PLAY_WAVE_FILE_TEST
	NewGO<PlayWaveFileTest>(0);
#endif
#ifdef MEMORY_LEAK_TEST
	NewGO<MemoryLeakTest>(0);
#else

	g_physicsWorld = NewGO<PhysicsWorld>(0);
	g_player = NewGO<Player>(0);
	NewGO<UnityChanInstance>(0);
	NewGO<EnemyManager>(0);
	NewGO<Map>(0);
	NewGO<Ground>(0);
	g_damageCollisionWorld = NewGO<DamageCollisionWorld>(0);

	Sky* sky = NewGO<Sky>(0);
	sky->SetPlayer(g_player);
	g_car = NewGO<Car>(0);
	g_camera = NewGO<GameCamera>(0);
	g_player->SetPosition(CVector3(-10.0f, 4.5f, 0.0f));
	g_camera->SetPlayer(g_player);
#endif
	Engine().RunGameLoop();		//ゲームループを実行。

	return 0;
}