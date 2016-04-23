/*!
 * @brief	キー入力
 */
 
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/Input/tkKeyInput.h"

namespace tkEngine{
	/*!
	 * @brief	コンストラクタ。
	 */
	CKeyInput::CKeyInput()
	{
		memset(m_keyPressFlag, 0, sizeof(m_keyPressFlag));
	}
	/*!
	 * @brief	デストラクタ。
	 */
	CKeyInput::~CKeyInput()
	{
	}
	/*!
	 * @brief	キー情報の更新。
	 */
	void CKeyInput::Update()
	{
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			m_keyPressFlag[enKeyUp] = true;
		}
		else {
			m_keyPressFlag[enKeyUp] = false;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			m_keyPressFlag[enKeyDown] = true;
		}
		else {
			m_keyPressFlag[enKeyDown] = false;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			m_keyPressFlag[enKeyRight] = true;
		}
		else {
			m_keyPressFlag[enKeyRight] = false;
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			m_keyPressFlag[enKeyLeft] = true;
		}
		else {
			m_keyPressFlag[enKeyLeft] = false;
		}
		if ((GetAsyncKeyState('A') & 0x8000) | (GetAsyncKeyState('a') & 0x8000) ) {
			m_keyPressFlag[enKeyA] = true;
		}
		else {
			m_keyPressFlag[enKeyA] = false;
		}
	}
}
