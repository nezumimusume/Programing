/*!
 *@brief	ShapeVertex。
 */

#ifndef _TKSHAPE_H_
#define _TKSHAPE_H_

namespace tkEngine{
	/*!
	 *@brief	カラーのみ頂点。
	 */
	struct ShapeVertex_Color{
		f32		pos[4];
		u32		color;
	}; 
}
#endif // _TKSHAPE_H_