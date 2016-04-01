#include "stdafx.h"
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/tkEngine.h"
#include "tkEngine/graphics/tkVertexBuffer.h"
#include "tkEngine/graphics/tkIndexBuffer.h"
#include "tkEngine/math/tkVector.h"

#define TEST_BUILD		//定義でテストビルド
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
	//初期化。
	SInitParam initParam;
	memset(&initParam, 0, sizeof(initParam));
	//コマンドバッファのサイズのテーブル。
	u32 commandBufferSizeTbl[] = {
		10 * 1024 * 1024,		//10MB
	};
	initParam.hInstance = hInst;
	initParam.gameObjectPrioMax = 255;
	initParam.numRenderContext = 1;	//レンダリングコンテキストは一本
	initParam.commandBufferSizeTbl = commandBufferSizeTbl;
	initParam.screenHeight = 720;
	initParam.screenWidth = 1280;
	CEngine::Instance().Init( initParam );	//初期化。
#ifdef TEST_BUILD
	CGameObjectManager::Instance().NewGameObject<CTest>(0);
#endif // #ifdef TEST_BUILD
	CEngine::Instance().RunGameLoop();		//ゲームループを実行。
	
	return 0;
}