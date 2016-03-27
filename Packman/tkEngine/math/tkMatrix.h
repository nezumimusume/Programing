/*!
 * @brief	行列。
 */

#ifndef _TKMATRIX_H_
#define _TKMATRIX_H_

#include "tkEngine/math/tkVector.h"

namespace tkEngine{
	/*!
	 * @brief	行列。
	 */
	class CMatrix{
	public:
		union {
			struct {
				f32 _11, _12, _13, _14;
				f32 _21, _22, _23, _24;
				f32 _31, _32, _33, _34;
				f32 _41, _42, _43, _44;
			};
			f32 m[4][4];
		};
		static const CMatrix Identity;	//!<単位行列。
	public:
		/*!
		* @brief	プロジェクション行列を作成。
		*@param[in]	viewAngle	画角。
		*@param[in]	aspect		アスペクト比。
		*@param[in]	fNear		近平面。
		*@param[in]	fFar		遠平面。
		*/
		void MakeProjectionMatrix(
			f32 viewAngle,
			f32 aspect,
			f32 fNear,
			f32 fFar
			)
		{
			D3DXMatrixPerspectiveFovRH(
				r_cast<D3DXMATRIX*>(this),
				viewAngle,
				aspect,
				fNear,
				fFar
			);
		}
		/*!
		 * @brief	注視点、上方向、カメラ位置からカメラ行列を作成。
		 *@param[in]	position	カメラ位置。
		 *@param[in]	target		注視点。
		 *@param[in]	up			カメラの上方向。
		 */
		void MakeLookAt( const CVector3& position, const CVector3& target, const CVector3& up )
		{
			D3DXMatrixLookAtRH(
				r_cast<D3DXMATRIX*>(this),
				r_cast<const D3DXVECTOR3*>(&position),
				r_cast<const D3DXVECTOR3*>(&target),
				r_cast<const D3DXVECTOR3*>(&up)
			);
		}
		/*!
		 *@brief	行列と行列の乗算
		 *@details
		 * 行列の計算順序は数学の記述に準拠する。
		 * *this = m0 * m1
		 */
		void Mul( const CMatrix& m0, const CMatrix& m1 )
		{
			D3DXMatrixMultiply(
				r_cast<D3DXMATRIX*>(this),
				r_cast<const D3DXMATRIX*>(&m0),
				r_cast<const D3DXMATRIX*>(&m1)
			);
		}
		/*!
		 *@brief	逆行列を計算。
		 *@param[in]	m	元になる行列。
		 */
		void Inverse( const CMatrix& m )
		{
			D3DXMatrixInverse(
				r_cast<D3DXMATRIX*>(this),
				NULL,
				r_cast<const D3DXMATRIX*>(&m)
			);
		}
		
	};
};
#endif // _TKMATRIX_H_