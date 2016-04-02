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
	CGameObjectManager::Instance().NewGameObject<CTestBoxRender>(0);
	CGameObjectManager::Instance().NewGameObject<CTestSphereRender>(0);
//	CGameObjectManager::Instance().NewGameObject<CTestCreateRenderTarget>(0);
}
void CTest::Update()
{

}
void CTest::Render(tkEngine::CRenderContext& renderContext)
{
	
}