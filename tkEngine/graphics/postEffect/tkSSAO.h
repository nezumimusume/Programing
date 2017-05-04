/*!
 * @brief	SSAO
 */

#pragma once

namespace tkEngine{
	/*!
	 * @brief	SSAO
	 */
	class CSSAO{
	public:
		/*!
		 * @brief	コンストラクタ。
		 */
		CSSAO();
		/*!
		 * @brief	デストラクタ。
		 */
		~CSSAO();
		/*!
		 * @brief	開放。
		 */
		void Release();
		/*!
		 * @brief	初期化。
		 *@param[in]	config		グラフィックコンフィグ。
		 */
		void Init(const SGraphicsConfig& config);
		/*!
		 * @brief	描画。
		 */
		void Render(CRenderContext& renderContext, CPostEffect* postEffect);
	private:
		bool		m_isEnable = false;		//!<SSAOが有効かどうかのフラグ。
		CEffect* 	m_effect = nullptr;
	};
}