#include "stdafx.h"
#include "Scene/TitleScene.h"
#include "Scene/GameScene.h"
#include "HUD/NowLoading.h"
#include "ScreenEffect/Fade.h"

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
	switch(state){
	case enState_Run:
		if (Pad(0).IsTrigger(enButtonStart)) {
			g_fade->StartFadeOut();
			state = enState_WaitFadeOut;
		}
		break;
	case enState_WaitFadeOut:
		if(!g_fade->IsExecute()){
			DeleteGO(this);
			g_nowLoading->SetActiveFlag(true);
			gameScene = NewGO<GameScene>(0);
		}
		break;
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