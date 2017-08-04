/*!
 *@brief	各種ライト
 */

#pragma once

namespace tkEngine{
	/*!
	 *@brief	ディレクションライト。
	 */
	struct SDirectionLight{
		CVector3	direction;		//!<ライトの方向。
		CVector3	color;			//!<ライトのカラー。
	};
	/*!
	 *@brief	アンビエントライト。
	 */
	struct SAmbientLight{
		CVector3	color;			//!<ライトのカラー。
	};
	/*!
	 *@brief	ポイントライト。
	 */
	struct SPointLight{
		CVector3	position;		//!<位置。
		CVector3	positionInView;	//!<ビュー空間での座標。
		CVector3	color;			//!<ライトのカラー。
		CVector4	attn;			//!<減衰定数。
	};
}