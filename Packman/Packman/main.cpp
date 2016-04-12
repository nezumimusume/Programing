#include "stdafx.h"
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/tkEngine.h"
#include "tkEngine/graphics/tkVertexBuffer.h"
#include "tkEngine/graphics/tkIndexBuffer.h"
#include "tkEngine/math/tkVector.h"
#include "Packman/game/CGameManager.h"
//#define TEST_BUILD		//定義でテストビルド
#ifdef TEST_BUILD
#include "test/test.h"
#endif
using namespace tkEngine;
int WINAPI wWinMain(
	HINSTANCE hInst, 
	HINSTANCE hPrevInstance, 
	LPWSTR lpCmdLine, 
	int nCmdShow 
){
	//エンジンを使用するための初期設定を行う。
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
	//輪郭線抽出処理の設定。
	initParam.graphicsConfig.edgeRenderConfig.isEnable = true;
	initParam.graphicsConfig.edgeRenderConfig.idMapWidth = initParam.frameBufferWidth;
	initParam.graphicsConfig.edgeRenderConfig.idMapHeight = initParam.frameBufferHeight;
	//Bloom
	initParam.graphicsConfig.bloomConfig.isEnable = true;
	//Shadow
	initParam.graphicsConfig.shadowRenderConfig.isEnable = true;
	initParam.graphicsConfig.shadowRenderConfig.shadowMapWidth = 1280;
	initParam.graphicsConfig.shadowRenderConfig.shadowMapHeight = 720;
	CEngine::Instance().Init( initParam );	//初期化。
#ifdef TEST_BUILD
	CGameObjectManager::Instance().NewGameObject<CTest>(0);
#else // #ifdef TEST_BUILD
	CGameObjectManager::Instance().NewGameObject<CGameManager>(0);
#endif
	CEngine::Instance().RunGameLoop();		//ゲームループを実行。
	
	return 0;
}