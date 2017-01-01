/*!
 *@brief	タイトルシーン。
 */

#pragma once


#include "tkEngine/Sound/tkSoundSource.h"

class TitleScene : public IGameObject{
public:
	/*!
	 *@brief	コンストラクタ。
	 */
	TitleScene();
	/*!
	 *@brief	デストラクタ。
	 */
	~TitleScene();
	void OnDestroy() override;
	void Update() override;
	bool Start() override;
	void PostRender(CRenderContext& renderContext) override;
private:
	enum EnState{
		enState_Run,			//実行中。
		enState_WaitFadeOut,	//フェードアウト待ち。
	};
	CSoundSource bgmSoundSource;
	CSprite		bg;
	CTexture	bgTex;
	EnState		state = enState_Run;
};