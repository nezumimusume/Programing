/*!
 *@brief	ポストエフェクト。
 */

#pragma once

#include "tkEngine/graphics/postEffect/tkFxaa.h"

namespace tkEngine{
	/*!
	 *@brief	ポストエフェクト。
	 */
	class CPostEffect : Noncopyable{
	public:
		/*!
		 *@brief	コンストラクタ。
		 */
		CPostEffect();
		/*!
		 *@brief	デストラクタ。
		 */
		~CPostEffect();
		/*!
		 *@brief	開放。
		 */
		void Release();
		/*!
		 *@brief	作成。
		 *@param[in]	config		コンフィグ。
		 */
		void Create( const SGraphicsConfig& config );
		/*!
		*@brief	描画。
		*@param[in]		rc		レンダリングコンテキスト。
		*/
		void Render(CRenderContext& rc);
	private:
		CFxaa	m_fxaa;		//!<FXAA。
	};
}