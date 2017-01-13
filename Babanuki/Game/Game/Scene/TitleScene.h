#pragma once
/*!
 *@brief	タイトルシーン。
 */
class TitleScene :
	public IGameObject
{
public:
	/*!
	 *@brief	コンストラクタ。
	 */
	TitleScene();
	/*!
	 *@brief	デストラクタ。
	 */
	~TitleScene();
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
	/*!
	*@brief	遅延描画関数。
	@details
	* ポストエフェクトの後で実行されます。HUDなどポストエフェクトの影響を受けたくない描画物はここでレンダリングしてください。
	*@param[in]		renderContext		レンダリングコンテキスト。
	*/
	void PostRender( CRenderContext& renderContext ) override;
private:
	//状態。
	enum EState {
		eStateWaitFadeIn,	//!<フェードイン待ち。
		eStateRun,			//!<実行中。
		eStateWaitFadeOut,	//!<フェードアウト待ち。
	};
	CSprite		m_titleBGSprite;		//!<タイトル画面の背景のスプライト。
	CTexture	m_titleBGTexture;		//!<タイトル画面の背景のテクスチャ。
	EState		m_state = eStateRun;	//!<状態。
};

