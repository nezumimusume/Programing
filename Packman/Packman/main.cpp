#include <Windows.h>
#include <mmsystem.h>
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/tkEngine.h"
#include "tkEngine/graphics/tkVertexBuffer.h"
#include "tkEngine/graphics/tkIndexBuffer.h"
#include "tkEngine/math/tkVector.h"

using namespace tkEngine;
class CTestGameObject : public IGameObject {
	void TestCreateVertexBuffer()
	{
		//頂点バッファの作成テスト。
		struct SVertex {
			float pos[4];
			float color[4];
		};
		SVertex vertices[] = {
			{
				(10.0f, 20.0f, 15.0f, 1.0f),
				(1.0f, 1.0f, 1.0f, 1.0f)
			},
			{
				(1.0f, 2.0f, 15.0f, 1.0f),
				(1.0f, 0.5f, 1.0f, 1.0f)
			},
			{
				(1.0f, 2.0f, 15.0f, 1.0f),
				(1.0f, 0.5f, 1.0f, 1.0f)
			},
			{
				(1.0f, 2.0f, 15.0f, 1.0f),
				(1.0f, 0.5f, 1.0f, 1.0f)
			},
		};
		CVertexBuffer vb;
		vb.Create(sizeof(vertices), vertices);
		vb.Release();
	}
	void TestCreateIndexBuffer()
	{
		u16 index[] = {
			0,1,2,3,4,5,6,7
		};

		CIndexBuffer ib;
		ib.Create(sizeof(index), eIndexFormat16, index);
		ib.Release();
	}
	void TestVector()
	{
		CVector3 v0, v1;
		v0.Add(v1);
		printf("%f %f %f", v0.x, v0.y, v0.z);
		printf("%f", v0.Dot(v1));
	}
	/*!
	*@brief	更新
	*/
	virtual void Update() override
	{
	//	TestCreateVertexBuffer();
	//	TestCreateIndexBuffer();
		TestVector();
	}
	/*!
	*@brief	描画
	*/
	virtual void Render(CRenderContext& renderContext) override
	{
		renderContext.SetRenderCommand(CRenderCommand_Clear(
			0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0
		));
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
	initParam.screenHeight = 720;
	initParam.screenWidth = 1280;
	CEngine::GetInstance().Init( initParam );	//初期化。
	CGameObjectManager::GetInstance().NewGameObject<CTestGameObject>(0);
	CEngine::GetInstance().RunGameLoop();		//ゲームループを実行。
	
	return 0;
}