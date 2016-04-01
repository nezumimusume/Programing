/*!
 * @brief	テストクラス。
 */
#include "stdafx.h"
#include "test.h"
#include "TestPrimitiveRender.h"
#include "TestBoxRender.h"
#include "tkEngine/tkEngine.h"
#include "TestSphereRender.h"
#include "tkEngine/graphics/tkGraphicsType.h"
#include "TestCreateRenderTarget.h"

using namespace tkEngine;

void CTest::Start()
{
	//CGameObjectManager::Instance().NewGameObject<CTestBoxRender>(0);
	CGameObjectManager::Instance().NewGameObject<CTestSphereRender>(0);
	CGameObjectManager::Instance().NewGameObject<CTestCreateRenderTarget>(0);
}
void CTest::Update()
{

}
void CTest::Render(tkEngine::CRenderContext& renderContext)
{
	renderContext.SetRenderCommand(CRenderCommand_Clear(
		0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0
		));
	tkEngine::SViewport vp = {
		0,
		0,
		tkEngine::CEngine::Instance().GetScreenWidth(),
		tkEngine::CEngine::Instance().GetScreenHeight(),
		0.0f,
		1.0f
	};
	renderContext.SetRenderCommand(CRenderCommand_SetViewport(vp));
	renderContext.SetRenderCommand(CRenderCommand_SetRenderState(RS_CULLMODE, CULL_NONE));
}