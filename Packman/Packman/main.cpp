#include <Windows.h>
#include <mmsystem.h>
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/tkEngine.h"

using namespace tkEngine;
class CTestGameObject : public IGameObject {
	/*!
	*@brief	更新
	*/
	virtual void Update() override
	{

	}
	/*!
	*@brief	描画
	*/
	virtual void Render(const CRenderContext& renderContext) override
	{

	}
};
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

	CEngine::GetInstance().Init( initParam );	//初期化。
	CGameObjectManager::GetInstance().NewGameObject<CTestGameObject>(0);
	CEngine::GetInstance().RunGameLoop();		//ゲームループを実行。
	
	return 0;
}