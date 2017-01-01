/*!
 *@brief	画面のフェードアウト/イン
 */

#pragma once

class Fade : public IGameObject{
public:
	Fade();
	~Fade();
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
	/*!
	*@brief	フェードの処理を実行中？。
	*@return フェードイン、フェードアウトを実行中はtrueを返します。
	*/
	bool IsExecute() const
	{
		return m_isExecute;
	}
	/*!
	*@brief	フェードアウトを開始。
	*/
	void StartFadeOut()
	{
		float alpha = m_sprite.GetAlpha();
		if (alpha < 1.0f) {
			m_timer = 0.0f;
			SetActiveFlag(true);
			m_isExecute = true;
			m_state = eFadeOut;
		}
	}
	/*!
	*@brief	フェードインを開始。
	*/
	void StartFadeIn()
	{
		float alpha = m_sprite.GetAlpha();
		if (alpha > 0.0f) {
			m_timer = 0.0f;
			SetActiveFlag(true);
			m_isExecute = true;
			m_state = eFadeIn;
		}
	}
private:
	//状態。
	enum EnState {
		eFadeOut,		//!<フェードアウト。
		eFadeIn,		//!<フェードイン。
	};
	const float FADE_TIME = 0.3f;		//!<フェードアウトの時間。(単位：秒)
	CSprite		m_sprite;				//!ブラックアウト用のスプライト。
	CTexture	m_texture;				//!<ブラックアウト用のテクスチャ。
	EnState		m_state = eFadeIn;		//!<状態。
	bool		m_isExecute = false;	//!<フェードを実行中？
	float		m_timer = 1.0f;			//!<タイマ(単位：秒)
};