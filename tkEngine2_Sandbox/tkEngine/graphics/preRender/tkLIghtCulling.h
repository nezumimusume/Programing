/*!
 *@brief	ライトカリング
 */

#pragma once

namespace tkEngine{
	/*!
	 *@brief	ライトカリング。
	 *@details
	 * TBFRの動的光源のタイルベースのカリングの処理。
	 */
	class CLightCulling{
	public:
		/*!
		 *@brief	コンストラクタ。
		 */
		CLightCulling();
		/*!
		 *@brief	デストラクタ。
		 */
		~CLightCulling();
		/*!
		 *@brief	ライトカリングの実行。
		 */
		void Render(CRenderContext& rc);
	private:
		
	};
}