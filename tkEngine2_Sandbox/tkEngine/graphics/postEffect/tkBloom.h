/*!
 * @brief	ブルーム
 */
#pragma once

namespace tkEngine{
	class CPostEffect;
	/*!
	 * @brief	ブルーム
	 */
	class CBloom : Noncopyable{
	public:
		/*!
		 * @brief	コンストラクタ。
		 */
		CBloom();
		/*!
		 * @brief	デストラクタ。
		 */
		~CBloom();
		/*!
		 * @brief	開放
		 */
		void Release();
		/*!
		 * @brief	初期化。
		 */
		void Init( const SGraphicsConfig& config );
		/*!
		 * @brief	描画
		 */
		void Render(CRenderContext& rc, CPostEffect* postEffect);
	private:
		static const int NUM_WEIGHTS = 8;
		static const int NUM_DOWN_SAMPLING_RT = 10;
		bool m_isEnable = false;		//!<有効。
		CRenderTarget m_luminanceRT;	//!<輝度を抽出するレンダリングターゲット。
		CRenderTarget m_combineRT;		//!<ぼかし合成用のレンダリングターゲット。
		CRenderTarget m_downSamplingRT[NUM_DOWN_SAMPLING_RT];	//!<ダウンサンプリング用のレンダリングターゲット。
		float m_weights[NUM_WEIGHTS];	//!<重みテーブル。
	};
}