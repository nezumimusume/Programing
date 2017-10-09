/*!
 * @brief	スプライト。
 */

#pragma once

namespace tkEngine{
	/*!
	 * @brief	スプライト。
	 */
	class CSprite{
	public:
		CSprite();
		~CSprite();
	private:
		CPrimitive		m_primitive;		//!<プリミティブ。
	};
}