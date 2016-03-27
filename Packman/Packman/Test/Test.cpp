/*!
 * @brief	テストクラス。
 */
#include "stdafx.h"
#include "test.h"
#include "TestPrimitiveRender.h"
using namespace tkEngine;

void CTest::Start()
{
	CGameObjectManager::GetInstance().NewGameObject<CTestPrimitiveRender>(0);
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
}