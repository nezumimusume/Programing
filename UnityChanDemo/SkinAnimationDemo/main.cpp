#include "stdafx.h"
#include "tkEngine/graphics/tkSkinModelData.h"
#include "tkEngine/graphics/tkSkinModel.h"
#include "tkEngine/graphics/tkAnimation.h"
#include "tkEngine/graphics/tkEffect.h"
#include "tkEngine/graphics/tkCamera.h"
#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/graphics/tkTexture.h"
#include "UnityChan.h"
#include "UnityChanInstance.h"

CCamera			*g_camera;				//カメラ。

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
		skinModel.Update(CVector3(0.0f, 0.0f, 0.0f), CQuaternion::Identity, CVector3::One);
	}
	void Map::Render(CRenderContext& renderContext) override
	{
		skinModel.Draw(renderContext, g_camera->GetViewMatrix(), g_camera->GetProjectionMatrix());
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
	initParam.frameBufferHeight = 1080;
	initParam.frameBufferWidth = 1920;
	initParam.graphicsConfig.bloomConfig.isEnable = false;
	//initParam.graphicsConfig.edgeRenderConfig.isEnable = true;
	initParam.graphicsConfig.edgeRenderConfig.idMapWidth = initParam.frameBufferWidth;
	initParam.graphicsConfig.edgeRenderConfig.idMapHeight = initParam.frameBufferHeight;
	//Shadow
	initParam.graphicsConfig.shadowRenderConfig.isEnable = true;
	initParam.graphicsConfig.shadowRenderConfig.shadowMapWidth = 2048;
	initParam.graphicsConfig.shadowRenderConfig.shadowMapHeight = 2048;
	Engine().Init(initParam);	//初期化。
	ShadowMap().SetNear(1.0f);
	ShadowMap().SetFar(10.0f);
	ShadowMap().SetLightPosition(CVector3(0.0f, 3.5f, 3.5f));
	CVector3 lightDir = CVector3(0.0f, -1.0f, -1.0f);
	lightDir.Normalize();
	ShadowMap().SetLightDirection(lightDir);
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
	//NewGO<UnityChanInstance>(0);
	for (int i = 0; i < 1; i++) {
		UnityChan* unityChan = NewGO<UnityChan>(0);
		if (i == 0) {
			unityChan->isUpdateAnim = true;
		}
		unityChan->SetPosition(CVector3(0.0f + 0.5f * i, 0.0f, 0.0f));
	}
	Engine().RunGameLoop();		//ゲームループを実行。
	
	return 0;
}