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
	SInitParam initParam;
	initParam.hInstance = hInst;
	CEngine::GetInstance().Init( initParam );	//初期化。
	CEngine::GetInstance().RunGameLoop();		//ゲームループを実行。
	
	return 0;
}