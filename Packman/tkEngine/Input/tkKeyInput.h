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
	private:
		bool	m_keyPressFlag[enKeyNum];
	};
}
#endif //_TKKEYINPUT_H_ 