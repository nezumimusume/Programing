/*!
 *@brief	球
 */

#ifndef _TKSPHERESHAPE_H_
#define _TKSPHERESHAPE_H_

#include "tkEngine/shape/tkShapeVertex.h"

namespace tkEngine{
	/*!
	 *@brief	球。
	 */
	class CSphereShape{
	public:
		/*!
		 *@brief	コンストラクタ。
		 */
		CSphereShape();
		/*!
		 *@brief	デストラクタ
		 */
		~CSphereShape();
		/*!
		 *@brief	カラースフィアを作成。
		 *@param[in]	radius	半径。
		 *@param[in]	grid	グリッド。
		 *@param[in]	color	カラー。
		 */
		void Create(f32 radius, f32 grid, u32 color);
		/*!
		 *@brief	リリース。
		 */
		void Release();
	private:
		bool m_isCreatePrimitive;		//!<内部でプリミティブを作成したかどうかのフラグ。
		CPrimitive* m_pPrimitive;		//!<プリミティブ。
		CVector3	m_position;			//!<座標。
		CQuaternion m_rotation;			//!<回転。
		CMatrix		m_worldMatrix;		//!<ワールド行列。
	};
}
#endif // _TKSPHERESHAPE_H_
