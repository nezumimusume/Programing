#include "stdafx.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ScreenEffect/Fade.h"

TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}
bool TitleScene::Start()
{
	m_titleBGTexture.Load("Assets/sprite/titleBG.png");
	m_titleBGSprite.Init(&m_titleBGTexture);
	g_fade->StartFadeIn();
	return true;
}
void TitleScene::Update()
{
	switch (m_state) {
	case eStateWaitFadeIn:
		if (!g_fade->IsExecute()) {
			m_state = eStateRun;
		}
		break;
	case eStateRun:
		if (Pad(0).IsPress(enButtonStart)) {
			g_fade->StartFadeOut();
			m_state = eStateWaitFadeOut;
		}
		break;
	case eStateWaitFadeOut:
		if (!g_fade->IsExecute()) {
			//フェード終わった。
			//ゲームシーンに遷移。
			g_gameScene = NewGO<GameScene>(0);
			//自分を削除。
			DeleteGO(this);
			return;
		}
		break;
	}
}
void TitleScene::PostRender(CRenderContext& renderContext)
{
	m_titleBGSprite.Draw(renderContext);
}