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
		u32	idMapWidth;		//!<IDマップの幅。
		u32 idMapHeight;	//!<IDマップの高さ。
	};
	
	/*!
	 * @brief	影処理のコンフィグ。
	 */
	struct SShadowRenderConfig{
		bool 	isEnable;			//!<影を落とす処理が有効かどうかのフラグ。
		u32		shadowMapWidth;		//!<シャドウマップの幅。
		u32		shadowMapHeight;	//!<シャドウマップの高さ。
	};
	
	/*!
	 * @brief	グラフィックスコンフィグ。
	 */
	struct SGraphicsConfig{
		SEdgeRenderConfig		edgeRenderConfig;		//!<エッジ抽出処理のコンフィグ。
		SShadowRenderConfig		shadowRenderConfig;		//!<影の処理のコンフィグ。
	};
}

#endif //_TKGRAPHICSCONFIG_H_