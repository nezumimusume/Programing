#include "stdafx.h"
#include "tkEngine/graphics/tkSkinModelData.h"
#include "tkEngine/graphics/tkSkinModel.h"
#include "tkEngine/graphics/tkEffect.h"
#include "tkEngine/graphics/tkCamera.h"

/*!
 * @brief	スキンモデル表示テスト
 */
class CSkinModelDrawTest : public IGameObject {
	CSkinModelData	m_skinModelData;		//スキンモデルデータ。
	CSkinModel		m_skinModel;			//スキンモデル。
	CCamera			m_camera;
public:
	void Start() override 
	{
		m_skinModelData.LoadModelData("Assets/modelData/tiny.x");
		//m_skinModelData.LoadModelData("Assets/modelData/tiger.x");
		m_skinModel.SetSkinModelData(&m_skinModelData);
		m_camera.SetPosition(CVector3(0.0f, 1.0f, -500.0f));
		m_camera.SetTarget(CVector3::Zero);
		m_camera.Update();
		m_camera.SetFar(1000.0f);
	}
	void Update() override 
	{
		m_skinModel.AddAnimation(1.0f / 60.0f);
		m_skinModel.UpdateWorldMatrix(CVector3::Zero, CQuaternion::Identity, CVector3::One);
	}
	void Render( CRenderContext& renderContext ) override
	{
		m_skinModel.Draw(renderContext, m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());
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
	//Shadow
	initParam.graphicsConfig.shadowRenderConfig.isEnable = true;
	initParam.graphicsConfig.shadowRenderConfig.shadowMapWidth = 1280;
	initParam.graphicsConfig.shadowRenderConfig.shadowMapHeight = 720;
	Engine().Init(initParam);	//初期化。
	ShadowMap().SetNear(2.0f);
	ShadowMap().SetFar(10.0f);
	ShadowMap().SetLightPosition(CVector3(0.0f, 3.5f, 0.0f));
	ShadowMap().SetLightDirection(CVector3(0.0f, -1.0f, -0.0f));
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
	GameObjectManager().NewGameObject<CSkinModelDrawTest>(0);
	Engine().RunGameLoop();		//ゲームループを実行。
	
	return 0;
}