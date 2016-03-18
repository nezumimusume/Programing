#include <Windows.h>
#include <mmsystem.h>
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/tkEngine.h"

using namespace tkEngine;
int WINAPI wWinMain(
	HINSTANCE hInst, 
	HINSTANCE hPrevInstance, 
	LPWSTR lpCmdLine, 
	int nCmdShow 
){
	//初期化。
	InitParam initParam;
	initParam.hInstance = hInst;
	Engine::GetInstance()->Init( initParam );	//初期化。
	Engine::GetInstance()->RunGameLoop();		//ゲームループを実行。
	Engine::GetInstance()->Final();				//終了処理。
	return 0;
}