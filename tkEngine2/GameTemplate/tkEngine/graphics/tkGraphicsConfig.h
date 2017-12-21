/*!
 * @brief	グラフィックスコンフィグ。
 */

#pragma once

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
		void Init()
		{
			isEnable = false;
			shadowMapWidth = 512;
			shadowMapHeight = 512;
			isEnableSoftShadow = false;
			nearPlane = UnitM(10.0f);
			farPlane = UnitM(100.0f);
			lightHeight = UnitM(20.0f);
			depthOffset[0] = 0.0002f;
			depthOffset[1] = 0.0002f;
			depthOffset[2] = 0.0002f;
		}
		bool 	isEnable;						//!<影を落とす処理が有効かどうかのフラグ。
		int		shadowMapWidth;					//!<シャドウマップの幅。
		int		shadowMapHeight;				//!<シャドウマップの高さ。
		float	nearPlane;						//!<近平面までの距離。				
		float	farPlane;						//!<遠平面までの距離。
		float	lightHeight;					//!<ライトの高さ。
		float	depthOffset[NUM_SHADOW_MAP];	//!<シャドウオフセット。この値を大きくすると、影が落ちにくくなる。
		bool	isEnableSoftShadow;				//!<ソフトシャドウが有効かどうかのフラグ。
	};
	/*!
	* @brief	Bloomのコンフィグ
	*/
	struct SBloomConfig {		
		bool	isEnable = false;		//!<ブルームが有効かどうかのフラグ。
	};
	/*!
	* @brief	リフレクションマップのコンフィグ
	*/
	struct SReflectionMapConfig {
		bool	isEnable = false;				//!<リフレクションマップが有効かどうかのフラグ。
		int		reflectionMapWidth;		//!<リフレクションマップの幅。
		int		reflectionMapHeight;	//!<リフレクションマップの高さ。
	};
	/*!
	* @brief	被写界深度のコンフィグ。
	*/
	struct SDofConfig {
		bool isEnable = false;					//被写界深度が有効かどうかのフラグ。
	};
	/*!
	* @brief	アンチエイリアスのコンフィグ。
	*/
	struct SAAConfig {
		bool isEnable = false;					//アンチエイリアスが有効かどうかのフラグ。
	};
	/*!
	* @brief	モーションブラーのコンフィグ。
	*/
	struct SMotionBlurConfig {
		bool isEnable = false;
	};
	/*!
	* @brief	トーンマップのコンフィグ。
	*/
	struct STonemapConfig {
		void Init()
		{
			isEnable = false;
			luminance = 0.34f;
		}
		bool isEnable = false;
		float luminance = 0.34f;			//明るさ。値が大きいほど明るくなります。
	};
	/*!
	* @brief	ディザリングのコンフィグ。
	*/
	struct SDitheringConfig {
		bool isEnable = false;
	};
	/*!
	 * @brief	グラフィックスコンフィグ。
	 */
	struct SGraphicsConfig{
		SEdgeRenderConfig		edgeRenderConfig;		//!<エッジ抽出処理のコンフィグ。
		SShadowRenderConfig		shadowRenderConfig;		//!<影の処理のコンフィグ。
		SBloomConfig			bloomConfig;			//!<Bloomのコンフィグ。
		SReflectionMapConfig	reflectionMapConfig;	//!<リフレクションマップのコンフィグ。
		SDofConfig				dofConfig;				//!<被写界深度のコンフィグ。
		SAAConfig				aaConfig;				//!<アンチエイリアスのコンフィグ。
		SMotionBlurConfig		motionBlurConfig;		//<!モーションブラーのコンフィグ。
		STonemapConfig			tonemapConfig;			//!<トーンマップのコンフィグ。
		SDitheringConfig		ditheringConfig;		//!<ディザリング。
	};
}
