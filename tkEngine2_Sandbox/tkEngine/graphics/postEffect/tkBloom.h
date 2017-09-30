/*!
 * @brief	ブルーム
 */
#pragma once

namespace tkEngine{
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
		void Render(CRenderContext& rc);
	private:
		bool m_isEnable = false;		//!<有効。
	};
}