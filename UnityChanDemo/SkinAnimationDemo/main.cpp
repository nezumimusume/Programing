#include "stdafx.h"

#include "UnityChan.h"
#include "UnityChanInstance.h"
#include "Car.h"
#include "Map.h"

//#define MEMORY_LEAK_TEST		//定義でメモリリークテストが有効になる。

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
		CSkinModelData	nonSkinModelData;		//スキンモデルデータ。
		nonSkinModelData.LoadModelData("Assets/modelData/Court.X", NULL);
		//スキンなしインスタンシングモデル。
		CSkinModelData nonSkinModelInstancing;
		nonSkinModelInstancing.LoadModelData("Assets/modelData/Court.X", NULL);
		//インスタンス描画用のデータを作成。
		tkEngine::SVertexElement vertexElement[] = {
			{ 1,  0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },  // WORLD 1行目
			{ 1, 16, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 },  // WORLD 2行目
			{ 1, 32, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3 },  // WORLD 3行目
			{ 1, 48, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 4 },  // WORLD 4行目
			D3DDECL_END()
		};
		nonSkinModelInstancing.CreateInstancingDrawData(10, vertexElement);
		//スキンありモデル。
		CSkinModelData skinModelData;
		skinModelData.LoadModelData("Assets/modelData/Unity.X", NULL);
		//スキンありインスタンシングモデル。
		CSkinModelData skinModelInstancing;
		skinModelInstancing.LoadModelData("Assets/modelData/Unity.X", NULL);
		skinModelInstancing.CreateInstancingDrawData(10, vertexElement);

	}
	void Render(CRenderContext& renderContext) override
	{

	}
};
#endif
class MapTest : public IGameObject {
	CSkinModelData	skinModelData;		//スキンモデルデータ。
	CSkinModel		skinModel;			//スキンモデル。
	CAnimation		animation;			//アニメーション。
	CLight			light;				//ライト。
	CTexture		normalMap;
public:
	MapTest()
	{
		skinModelData.LoadModelData("Assets/modelData/Court.X", NULL);
		skinModel.Init(&skinModelData);
		skinModel.SetLight(&light);
		normalMap.Load("Assets/modelData/Grass_Normals.tga");
		skinModel.SetNormalMap(&normalMap);
		light.SetDiffuseLightDirection(0, CVector3(0.707f, 0.0f, -0.707f));
		light.SetDiffuseLightDirection(1, CVector3(-0.707f, 0.0f, -0.707f));
		light.SetDiffuseLightDirection(2, CVector3(0.0f, 0.707f, -0.707f));
		light.SetDiffuseLightDirection(3, CVector3(0.0f, -0.707f, -0.707f));

		light.SetDiffuseLightColor(0, CVector4(0.2f, 0.2f, 0.2f, 1.0f));
		light.SetDiffuseLightColor(1, CVector4(0.2f, 0.2f, 0.2f, 1.0f));
		light.SetDiffuseLightColor(2, CVector4(0.2f, 0.2f, 0.2f, 1.0f));
		light.SetDiffuseLightColor(3, CVector4(0.2f, 0.2f, 0.2f, 1.0f));
		light.SetAmbinetLight(CVector3(0.4f, 0.4f, 0.4f));
		skinModel.SetShadowReceiverFlag(true);
	}
	~MapTest()
	{

	}
	void Start() override
	{

	}
	void Update() override
	{
		skinModel.Update(CVector3(0.0f, -0.05f, 0.0f), CQuaternion::Identity, CVector3(10.0f, 1.0f, 10.0f));
	}
	void Render(CRenderContext& renderContext) override
	{
		skinModel.Draw(renderContext, g_camera->GetCamera().GetViewMatrix(), g_camera->GetCamera().GetProjectionMatrix());
	}
};
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
	initParam.graphicsConfig.bloomConfig.isEnable = false;
	initParam.graphicsConfig.edgeRenderConfig.isEnable = false;
	initParam.graphicsConfig.edgeRenderConfig.idMapWidth = initParam.frameBufferWidth;
	initParam.graphicsConfig.edgeRenderConfig.idMapHeight = initParam.frameBufferHeight;
	//Shadow
	initParam.graphicsConfig.shadowRenderConfig.isEnable = true;
	initParam.graphicsConfig.shadowRenderConfig.shadowMapWidth = 2048;
	initParam.graphicsConfig.shadowRenderConfig.shadowMapHeight = 2048;
	//reflection
	initParam.graphicsConfig.reflectionMapConfig.isEnable = true;
	initParam.graphicsConfig.reflectionMapConfig.reflectionMapWidth = 512;
	initParam.graphicsConfig.reflectionMapConfig.reflectionMapHeight = 512;
	Engine().Init(initParam);	//初期化。

	ShadowMap().SetNear(2.0f);
	ShadowMap().SetFar(20.0f);
	
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
	
#ifdef MEMORY_LEAK_TEST
	NewGO<MemoryLeakTest>(0);
#else
	NewGO<MapTest>(0);
	NewGO<Map>(0);
	NewGO<UnityChanInstance>(0);
	
	UnityChan* unityChan = NewGO<UnityChan>(0);
	g_car = NewGO<Car>(0);
	g_camera = NewGO<GameCamera>(0);
	unityChan->SetPosition(CVector3(0.0f, 0.0f, 0.0f));
	g_camera->SetUnityChan(unityChan);
#endif
	Engine().RunGameLoop();		//ゲームループを実行。
	
	return 0;
}