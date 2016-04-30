/*!
 * @brief	グラフィックスコンフィグ。
 */

#ifndef _TKGRAPHICSCONFIG_H_
#define _TKGRAPHICSCONFIG_H_

namespace tkEngine{
	/*!
	 * @brief	エッジ抽出処理のコンフィグ
	 */
	struct SEdgeRenderConfig{
		bool isEnable;		//!<エッジ抽出処理が有効かどうかのフラグ。
		int	idMapWidth;		//!<IDマップの幅。
		int idMapHeight;	//!<IDマップの高さ。
	};
	
	/*!
	 * @brief	影処理のコンフィグ。
	 */
	struct SShadowRenderConfig{
		bool 	isEnable;			//!<影を落とす処理が有効かどうかのフラグ。
		int		shadowMapWidth;		//!<シャドウマップの幅。
		int		shadowMapHeight;	//!<シャドウマップの高さ。
	};
	/*!
	* @brief	Bloomのコンフィグ
	*/
	struct SBloomConfig {
		bool	isEnable;		//!<ブルームが有効かどうかのフラグ。
	};
	/*!
	 * @brief	グラフィックスコンフィグ。
	 */
	struct SGraphicsConfig{
		SEdgeRenderConfig		edgeRenderConfig;		//!<エッジ抽出処理のコンフィグ。
		SShadowRenderConfig		shadowRenderConfig;		//!<影の処理のコンフィグ。
		SBloomConfig			bloomConfig;			//!<Bloomのコンフィグ。
	};
}

#endif //_TKGRAPHICSCONFIG_H_