/*!
 *@brief	ShapeVertex。
 */

#ifndef _TKSHAPE_H_
#define _TKSHAPE_H_

namespace tkEngine{
	/*!
	 *@brief	カラー。
	 */
	struct SShapeVertex_PC{
		f32		pos[4];
		u32		color;
	}; 
	/*!
	*@brief	カラー＋法線。
	*/
	struct SShapeVertex_PNC {
		f32		pos[4];
		f32		normal[3];
		u32		color;	
	};
}
#endif // _TKSHAPE_H_