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
	void Start() override;
private:
	CSoundSource bgmSoundSource;
};