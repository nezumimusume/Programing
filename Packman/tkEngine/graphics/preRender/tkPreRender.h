/*!
 * @brief	プリレンダー
 */

#ifndef _TKPRERENDER_H_
#define _TKPRERENDER_H_

#include "tkEngine/graphics/preRender/tkPreRender.h"

namespace tkEngine{
	/*!
	 * @brief	プリレンダリング。
	 */
	class CPreRender{
	public:
		CPreRender();
		~CPreRender();
		void Create( u32 effectFlags );
	private:
		CIDMap		m_idMap;		//!<IDマップ
	};
}
#endif //_TKPRERENDER_H_