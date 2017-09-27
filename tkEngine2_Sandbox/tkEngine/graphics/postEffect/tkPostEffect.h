/*!
 *@brief	ポストエフェクト。
 */

#pragma once

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
	};
}