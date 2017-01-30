/*!
 *@brief	トーンマップ。
 */
#pragma once

namespace tkEngine{
	/*!
	 *@brief	トーンマップ。
	 */
	class CTonemap{
	public:
		CTonemap();
		~CTonemap();
		/*!
		*@brief	作成。
		*@param[in]		config		グラフィック設定。
		*/
		void Create(const SGraphicsConfig& config);
		/*!
		 *@brief	平均輝度の計算。
		 *@param[in]	renderContext		レンダリングコンテキスト
		 */
		void CalcLuminanceAvarage(CRenderContext& renderContext, CPostEffect* postEffect);
		/*!
		 *@brief	トーンマップの実行。
		 *@details
		 * この関数を呼ぶ前にCalcLuminanceAvarageをコールして平均輝度の計算を行ってください。
		 * 平均輝度の計算はポストエフェクトの戦闘で行ってください。
		 *@param[in]	renderContext		レンダリングコンテキスト
		 */
		void Execute(CRenderContext& renderContext, CPostEffect* postEffect);
	private:
		static const int NUM_CALC_AVG_RT = 5;			//!<平均輝度計算用のレンダリングターゲットの枚数。
		CEffect*		m_effect = nullptr;				//!<エフェクト。
		bool			m_isEnable = false;				//!<トーンマップ有効？
		CRenderTarget	m_calcAvgRT[NUM_CALC_AVG_RT];	//!<平均輝度計算用のレンダリングターゲット。
		float			m_fMiddleGray = 0.001f;			//!<この値を大きくすると明るくなる。
	};
}