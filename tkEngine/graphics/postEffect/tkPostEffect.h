/*!
 * @brief	ポストエフェクト
 */

#ifndef _TKPOSTEFFECT_H_
#define _TKPOSTEFFECT_H_

#include "tkEngine/graphics/postEffect/tkEdgeRender.h"
#include "tkEngine/graphics/postEffect/tkBloomRender.h"

namespace tkEngine{
	/*!
	 * @brief	ポストエフェクト。
	 */
	class CPostEffect{
	public:
		/*!
		 * @brief	コンストラクタ。
		 */
		CPostEffect();
		/*!
		 * @brief	デストラクタ。
		 */
		~CPostEffect();
		/*!
		 * @brief
		 */
		void Create( const SGraphicsConfig& config );
		/*!
		* @brief	描画。
		*/
		void Render(CRenderContext& renderContext);
		/*!
		* @brief	フルスクリーン描画。
		*/
		void RenderFullScreen(CRenderContext& renderContext);
	private:
		CEdgeRender		m_edgeRender;		//!<エッジ描画。
		CBloomRender	m_bloomRender;		//!<Bloom。
		CPrimitive		m_fullscreenRenderPrim;	//!<フルスクリーンをレンダリングするためのプリミティブ。
	};
}

#endif // _TKPOSTEFFECT_H_
