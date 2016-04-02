/*!
 * @brief	プリレンダー
 */

#ifndef _TKPRERENDER_H_
#define _TKPRERENDER_H_

#include "tkEngine/graphics/tkGraphicsConfig.h"

namespace tkEngine{
	/*!
	 * @brief	プリレンダリング。
	 */
	class CPreRender{
	public:
		CPreRender();
		~CPreRender();
		void Create( const SGraphicsConfig& config );
	private:
		CIDMap		m_idMap;		//!<IDマップ
	};
}
#endif //_TKPRERENDER_H_