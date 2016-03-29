/*!
 *@brief	グラフィックス関係の型定義
 */
 
#ifndef _TKGRAPHICSTYPE_H_
#define _TKGRAPHICSTYPE_H_

namespace tkEngine{
	/*!
	 *@brief	ビューポート。
	 */
	struct SViewport{
		u32		x;		//!<ビューポートの左上のx座標(スクリーン座標系)
		u32		y;		//!<ビューポートの左上のy座標(スクリーン座標系)
		u32		width;	//!<ビューポートの幅。
		u32		height;	//!<ビューポートの高さ。
		f32		minZ;	//!<近平面。
		f32		maxZ;	//!<遠平面。
	};
}

#endif //_TKGRAPHICSTYPE_H_