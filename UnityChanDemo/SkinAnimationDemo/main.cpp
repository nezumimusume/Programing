#include "stdafx.h"

#include "UnityChan.h"
#include "UnityChanInstance.h"



class Map : public IGameObject {
	CSkinModelData	skinModelData;		//スキンモデルデータ。
	CSkinModel		skinModel;			//スキンモデル。
	CAnimation		animation;			//アニメーション。
	CLight			light;				//ライト。
public:
	Map()
	{
		skinModelData.LoadModelData("Assets/modelData/Court.X", NULL);
		skinModel.Init(&skinModelData);
		skinModel.SetLight(&light);

		light.SetDiffuseLightDirection(0, CVector3(0.707f, 0.0f, -0.707f));
		light.SetDiffuseLightDirection(1, CVector3(-0.707f, 0.0f, -0.707f));
		light.SetDiffuseLightDirection(2, CVector3(0.0f, 0.707f, -0.707f));
		light.SetDiffuseLightDirection(3, CVector3(0.0f, -0.707f, -0.707f));

		light.SetDiffuseLightColor(0, CVector4(0.5f, 0.5f, 0.5f, 1.0f));
		light.SetDiffuseLightColor(1, CVector4(0.5f, 0.5f, 0.5f, 1.0f));
		light.SetDiffuseLightColor(2, CVector4(0.5f, 0.5f, 0.5f, 1.0f));
		light.SetDiffuseLightColor(3, CVector4(0.5f, 0.5f, 0.5f, 1.0f));
		light.SetAmbinetLight(CVector3(0.3f, 0.3f, 0.3f));
		skinModel.SetShadowReceiverFlag(true);
	}
	~Map()
	{

	}
	void Map::Start() override
	{

	}
	void Map::Update() override
	{
		skinModel.Update(CVector3(0.0f, -0.05f, 0.0f), CQuaternion::Identity, CVector3(10.0f, 1.0f, 10.0f));
	}
	void Map::Render(CRenderContext& renderContext) override
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
	initParam.graphicsConfig.bloomConfig.isEnable = true;
	initParam.graphicsConfig.edgeRenderConfig.isEnable = false;
	initParam.graphicsConfig.edgeRenderConfig.idMapWidth = initParam.frameBufferWidth;
	initParam.graphicsConfig.edgeRenderConfig.idMapHeight = initParam.frameBufferHeight;
	//Shadow
	initParam.graphicsConfig.shadowRenderConfig.isEnable = true;
	initParam.graphicsConfig.shadowRenderConfig.shadowMapWidth = 1024;
	initParam.graphicsConfig.shadowRenderConfig.shadowMapHeight = 1024;
	//reflection
	initParam.graphicsConfig.reflectionMapConfig.isEnable = true;
	initParam.graphicsConfig.reflectionMapConfig.reflectionMapWidth = 512;
	initParam.graphicsConfig.reflectionMapConfig.reflectionMapHeight = 512;
	Engine().Init(initParam);	//初期化。
	
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
	
	NewGO<Map>(0);
	NewGO<UnityChanInstance>(0);
	UnityChan* unityChan = NewGO<UnityChan>(0);
	g_camera = NewGO<GameCamera>(0);
	unityChan->SetPosition(CVector3(0.0f, 0.0f, 0.0f));
	g_camera->SetUnityChan(unityChan);

	Engine().RunGameLoop();		//ゲームループを実行。
	
	return 0;
}