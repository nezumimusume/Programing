/*!
 * @brief	キー入力。
 */

#ifndef _TKKEYINPUT_H_ 
#define _TKKEYINPUT_H_ 

namespace tkEngine{
	class CKeyInput{
		enum EnKey{
			enKeyUp,
			enKeyDown,
			enKeyRight,
			enKeyLeft,
			enKeyA,
			enKeyNum,
		};
	public:
		/*!
		 * @brief	コンストラクタ。
		 */
		CKeyInput();
		/*!
		 * @brief	デストラクタ。
		 */
		~CKeyInput();
		/*!
		 * @brief	キー情報の更新。
		 */
		void Update();
		/*!
		 * @brief	上キーが押されている。
		 */
		bool IsUpPress() const
		{
			return m_keyPressFlag[enKeyUp];
		}
		/*!
		 * @brief	右キーが押されている。
		 */
		bool IsRightPress() const
		{
			return m_keyPressFlag[enKeyRight];
		}
		/*!
		 * @brief	左キーが押されている。
		 */
		bool IsLeftPress() const
		{
			return m_keyPressFlag[enKeyLeft];
		}
		/*!
		 * @brief	下キーが押されている。
		 */
		bool IsDownPress() const
		{
			return m_keyPressFlag[enKeyDown];
		}
		/*!
		* @brief	キーボードのAが押された。
		*/
		bool IsPressA() const
		{
			return m_keyPressFlag[enKeyA];
		}
		/*!
		* @brief	キーボードのAのトリガー判定。
		*/
		bool IsTrggerA() const
		{
			return m_keyTrigerFlag[enKeyA];
		}
		/*!
		* @brief	マウスの左ボタンが離されたときの処理。
		*/
		void OnMouseLButtonUp(int x, int y)
		{
			m_mousePositionX = x;
			m_mousePositionY = y;
			m_isMouseUp[1] = true;
		}
		/*!
		* @brief	マウスの左ボタンが離されたときか判定。
		*/
		bool IsMouseLButtonUp() const
		{
			return m_isMouseUp[0];
		}
		/*!
		* @brief	マウスのX座標を取得。
		*/
		int GetMousePositionX() const
		{
			return m_mousePositionX;
		}
		/*!
		* @brief	マウスのY座標を取得。
		*/
		int GetMousePositionY() const
		{
			return m_mousePositionY;
		}
	private:
		bool	m_keyPressFlag[enKeyNum];
		bool	m_keyTrigerFlag[enKeyNum];
		bool	m_isMouseUp[2];
		int		m_mousePositionX;
		int		m_mousePositionY;
	};
}
#endif //_TKKEYINPUT_H_ 