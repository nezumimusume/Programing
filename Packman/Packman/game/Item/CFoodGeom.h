/*!
 *@brief	食べ物の形状クラス。
 */

#ifndef _CFOODGEOM_H_
#define _CFOODGEOM_H_

#include "tkEngine/shape/tkSphereShape.h"

class CFoodGeom{
public:
	/*!
	 *@brief	コンストラクタ。
	 */
	CFoodGeom();
	/*!
	 *@brief	デストラクタ。
	 */
	~CFoodGeom();
	/*!
	 *@brief	構築。
	 *@param[in]	radius		半径
	 */
	void Build( f32 radius );
private:
	tkEngine::CSphereShape	m_sphere;
};

#endif //_CFOODGEOM_H_