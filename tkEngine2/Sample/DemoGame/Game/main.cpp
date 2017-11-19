/*!
 *@brief	main.cpp
 */
#include "stdafx.h"
#include "Game.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	srand((unsigned)time(NULL));
	//tkEngine2の初期化パラメータを設定する。
	SInitParam initParam;
	initParam.nCmdShow = nCmdShow;
	initParam.hInstance = hInstance;
	initParam.screenWidth = 1280;
	initParam.screenHeight = 720;
	initParam.frameBufferWidth = 1280;
	initParam.frameBufferHeight = 720;
	initParam.screenWidth2D = 1280;
	initParam.screenHeight2D = 720;
	//影の設定。
	initParam.graphicsConfing.shadowRenderConfig.isEnable = true;
	initParam.graphicsConfing.shadowRenderConfig.shadowMapWidth = 2048;
	initParam.graphicsConfing.shadowRenderConfig.shadowMapHeight = 2048;
	initParam.graphicsConfing.shadowRenderConfig.isEnableSoftShadow = true;
	//アンチ
	initParam.graphicsConfing.aaConfig.isEnable = true;
	//Bloom
	initParam.graphicsConfing.bloomConfig.isEnable = true;
	//tonemap
	initParam.graphicsConfing.tonemapConfig.isEnable = true;
	//ディザリング。
	initParam.graphicsConfing.ditheringConfig.isEnable = true;

	MainCamera().SetNear(100.0f);
	MainCamera().SetFar(10000.0f);
	GraphicsEngine().GetShadowMap().SetFar(5000.0f);
	GraphicsEngine().GetShadowMap().SetNear(500.0f);
	
	//エンジンを初期化。
	if (Engine().Init(initParam) == true) {
		GraphicsEngine().GetTonemap().SetLuminance(0.34f);
		SoundEngine().GetMasteringVoice()->SetVolume(0.2f);
		NewGO<Game>(0, "Game");
		//ゲームループを実行。
		Engine().RunGameLoop();
	}
	//エンジンの終了処理。
	Engine().Final();

	return 0;
}

