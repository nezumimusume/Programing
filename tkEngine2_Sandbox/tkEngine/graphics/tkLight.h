/*!
 *@brief	各種ライト
 */

#pragma once

namespace tkEngine{
	/*!
	 *@brief	ディレクションライト。
	 */
	struct SDirectionLight{
		CVector4	color;			//!<ライトのカラー。
		CVector3	direction;		//!<ライトの方向。
	};
	/*!
	 *@brief	アンビエントライト。
	 */
	struct SAmbientLight{
		CVector3	color;			//!<ライトのカラー。
	};
	/*!
	 *@brief	ポイントライト。
	 *@details
	 * このパラメータを変更したら、LightCulling.fxとmodelStruct.hを変更するように。
	 */
	struct SPointLight{
		CVector3	position;		//!<位置。
		CVector3	positionInView;	//!<ビュー空間での座標。
		CVector4	color;			//!<ライトのカラー。
		CVector4	attn;			//!<減衰定数。
	};
}