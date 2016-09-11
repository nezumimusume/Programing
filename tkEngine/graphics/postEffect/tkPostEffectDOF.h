/*!
 * @brief	被写界深度
 */

#pragma once

#include "tkEngine/graphics/tkGaussianBlur.h"

namespace tkEngine{
	class CPostEffect;
	/*!
	 * @brief	被写界深度
	 */
	class CDof : Noncopyable{
	public:
		/*!
		 * @brief	コンストラクタ。
		 */
		CDof();
		/*!
		 * @brief	デストラクタ。
		 */
		~CDof();
		/*!
		 * @brief	描画。
		 */
		void Render( CRenderContext& renderContext, CPostEffect* postEffect );
		/*!
		* @brief	作成。
		*@param[in]	config		グラフィックコンフィグ。
		*/
		void Create(const SGraphicsConfig& config);
		/*!
		* @brief	深度を書き込むレンダリングターゲットの取得。
		*/
		CRenderTarget* GetDepthRenderTarget()
		{
			return &m_depthRT;
		}
		/*!
		* @brief	開放。
		*/
		void Release();
	private:
		CRenderTarget		m_depthRT;		//!<深度を書き込むレンダリングターゲット。
		bool				m_isEnable;		//!<DOF有効？
		CGaussianBlur		m_blurForward;	//!<前ボケ用のブラー。
		CGaussianBlur		m_blurBack;		//!<奥ボケ用のブラー。
		CEffect*			m_effect;		//!<エフェクト。
	};
}
