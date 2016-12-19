#include "stdafx.h"
#include "Scene/TitleScene.h"
#include "Scene/GameScene.h"
#include "HUD/NowLoading.h"

TitleScene::TitleScene()
{
}
TitleScene::~TitleScene()
{
}
void TitleScene::OnDestroy()
{
	DeleteGO(&bgmSoundSource);
}
void TitleScene::Update()
{
	if (Pad(0).IsTrigger(enButtonStart)) {
		DeleteGO(this);
		g_nowLoading->SetActiveFlag(true);
		NewGO<GameScene>(0);
	}
}
bool TitleScene::Start()
{
	bgmSoundSource.InitStreaming("Assets/sound/titleBgm.wav");
	bgmSoundSource.Play(true);
	AddGO(0, &bgmSoundSource);
	bgTex.Load("Assets/Sprite/titleBG.jpg");
	bg.Init(&bgTex);
	CVector2 size;
	size.x = (float)Engine().GetFrameBufferWidth();
	size.y = (float)Engine().GetFrameBufferHeight();
	bg.SetSize(size);
	return true;
}
void TitleScene::PostRender(CRenderContext& renderContext)
{
	bg.Draw(renderContext);
}