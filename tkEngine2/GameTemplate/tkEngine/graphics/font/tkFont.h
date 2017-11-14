/*!
 * @brief	フォント
 */

#pragma once

namespace tkEngine{
	/*!
	 * @brief	フォント。
	 */
	class CFont{
	public:
		CFont();
		~CFont();
		/*!
		 * @brief	描画開始。
		 */
		void Begin();
		/*!
		 * @brief	描画終了。
		 */
		void End();
		/*!
		 * @brief	描画。
		 *@param[in]	text		表示したいテキスト。
		 *@param[in]	trans		平行移動。
		 *@param[in]	color		カラー。
		 *@param[in]	rot			回転。
		 *@param[in]	scale		拡大。
		 *@param[in]	pivot		基点。
		 *						0.5, 0.5で画像の中心が基点。
		 *						0.0, 0.0で画像の左下。
		 *						1.0, 1.0で画像の右上。
		 *						UnityのuGUIに準拠。
		 */
		void Draw(
			wchar_t const* text, 
			const CVector2& position, 
			const CVector4& color = CVector4::White,
			float rotation = 0.0f, 
			float scale = 1.0f,
			CVector2 pivot = {0.5f, 0.5f}
		);
	private:
		DirectX::SpriteBatch*	m_spriteBatch = nullptr;	//!<スプライトバッチ。
		DirectX::SpriteFont*	m_spriteFont = nullptr;		//!<スプライトフォント。
	};
}