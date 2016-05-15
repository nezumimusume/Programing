/*!
 *@brief	レンダリングターゲットの作成テスト。
 */

#include "stdafx.h"
#include "test/TestCreateRenderTarget.h"

void CTestCreateRenderTarget::Start()
{
}
void CTestCreateRenderTarget::Update()
{
	m_renderTarget.Create(
		1280,
		720,
		1,
		tkEngine::FMT_A8R8G8B8,
		tkEngine::FMT_D16,
		tkEngine::MULTISAMPLE_NONE,
		0
	);
	m_renderTarget.Release();
}
void CTestCreateRenderTarget::Render(tkEngine::CRenderContext& renderContext)
{
}
