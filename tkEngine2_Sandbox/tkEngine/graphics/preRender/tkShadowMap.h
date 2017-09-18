/*!
 * @brief	シャドウマップ
 */

#pragma once

namespace tkEngine{
	/*!
	 * @brief	シャドウマップ。
	 */
	class CShadowMap : Noncopyable{
	public:
		static const int MAX_SHADOW_MAP = 3;
		/*!
		 * @brief	コンストラクタ。
		 */
		CShadowMap();
		/*!
		 * @brief	デストラクタ。
		 */
		~CShadowMap();
		/*!
		 * @brief	シャドウマップの作成。
		 *@param[in]	config		コンフィグ。
		 *@return	trueが返ってきたらシャドウマップの作成成功。
		 */
		bool Init( const SShadowRenderConfig& config );
		
	private:
		bool m_isEnable = false;							//!<影の処理が有効？
		CRenderTarget	m_shadowMapRT[MAX_SHADOW_MAP];		//!<シャドウマップを書き込むレンダリングターゲット。
		int m_numShadowMap = 0;								//!<シャドウマップの枚数。
	};
}