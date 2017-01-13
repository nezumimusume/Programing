#pragma once

#include "Common/CardDeck.h"
#include "Player.h"
#include "tkEngine/Sound/tkSoundSource.h"

/*!
 *@brief	ゲームシーン。
 */
class GameScene :
	public IGameObject
{
public:
	/*!
	 *@brief	コンストラクタ。
	 */
	GameScene();
	/*!
	 *@brief	デストラクタ。
	 */
	~GameScene();
	/*!
	 *@brief	開始関数。
	 *@details
	 * 初期化などをこの関数に実装してください。</br>
	 * この関数がtrueを返すと本館数は以降のフレームでは呼ばれなくなります。</br>
	 * そしてゲームオブジェクトの状態が初期化完了になりUpdate関数が呼ばれるようになります。</br>
	 *@return	trueが帰ってきたら初期化完了。
	 */
	bool Start() override;
	/*!
	 *@brief	更新関数。
	 */
	void Update() override;
	void Render(CRenderContext& rc);
	void OnDestroy() override;
	/*!
	*@brief	カメラを取得。
	*/
	const CCamera& GetCamera() const
	{
		return camera;
	}
	/*!
	*@brief	ライトを取得。
	*/
	CLight& GetLight() 
	{
		return light;
	}
private:
	/*!
	*@brief	勝敗判定。
	*/
	bool Judgement();
private:
	//初期化ステータス
	enum EnInitState{
		enInitState_Init00,			//!<初期化ステップ00。
		enInitState_WaitInit,
		
	};
	enum EnGameStep {
		enGameStep_DealCards,		//!<カードを配る。
		enGameStep_WaitFadeIn,		//!<フェードイン待ち。
		enGameStep_SelectPlayer,	//!<プレイヤーがカードを選択中。
		enGameStep_SelectCom,		//!<COMがカードを選択中。
		enGameStep_Over,			//!<終わり。
		enGameStep_WaitFadeOut,		//!<フェードアウト待ち。
	};
	static const int NUM_PLAYER = 2;
	EnInitState m_initState = enInitState_Init00;
	CardDeck cardDeck;				//!<カードデッキ。
	CCamera camera;					//!<カメラ。
	CLight  light;					//!<ライト。
	Player  playerList[NUM_PLAYER];		//!<プレイヤーのリスト
	CTexture*	textureBG;				//!<背景のテクスチャ。
	CSprite		spriteBG;				//!<背景のスプライト。
	EnGameStep gameStep = enGameStep_DealCards;
	// HansOn-1 BGMを再生するためのCSoundSourceのメンバ変数を追加。
	CSoundSource* bgmSource = NULL;
};

extern GameScene* g_gameScene;
