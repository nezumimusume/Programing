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
		/*!
		*@brief	トーンマップの処理をリセット。
		*@details
		*　輝度が大きく変わるシーン切り替えなどが発生する場合などに明暗順応がおかしく見える場合があります。
		* そのような場合はシーン切り替えのタイミングでリセットを行ってみてください。
		*/
		void Reset()
		{
			m_isFirstWhenChangeScene = true;
		}
	private:
		static const int NUM_CALC_AVG_RT = 5;				//!<平均輝度計算用のレンダリングターゲットの枚数。
		CEffect*		m_effect = nullptr;					//!<エフェクト。
		bool			m_isEnable = false;					//!<トーンマップ有効？
		CRenderTarget	m_calcAvgRT[NUM_CALC_AVG_RT];		//!<平均輝度計算用のレンダリングターゲット。
		CRenderTarget   m_avgRT[2];							//!<平均輝度が格納されるレンダリングターゲット。
		int				m_currentAvgRT = 0;					//!<
		float			m_fMiddleGray = 0.22f;				//!<この値を大きくすると明るくなる。
		bool			m_isFirstWhenChangeScene = true;	//!<シーンが切り替わって初回の描画かどうかのフラグ。
	};
}