/*!
 * @brief	IDマップ
 */

#ifndef _TKIDMAP_H_
#define _TKIDMAP_H_

#include "tkEngine/graphics/tkRenderTarget.h"

namespace tkEngine{
	class CIDMap{
	public:
		/*!
		 * @brief	コンストラクタ
		 */
		CIDMap();
		/*!
		 * @brief	デストラクタ。
		 */
		~CIDMap();
		/*!
		 * @brief	IDマップの作成。
		 */
		void Create(u32 w, u32 h);
		/*!
		 * @brief	開放。
		 */
		void Release();
		/*!
		 * @brief	IDマップに書き込み
		 *@param[in]	renderContext	レンダリングコンテキスト。
		 */
		void RenderToIDMap( CRendeContext& renderContext );
	private:
		CRenderTarget				m_idMapRT;	//!<IDマップを書き込むレンダリングターゲット。
		std::vector<IGameObject>	
		
	};
}
#endif // _TKIDMAP_H_
