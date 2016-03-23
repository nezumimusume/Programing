/*!
 * @brief	ベクトル
 */

#ifndef _TKVECTOR_H_
#define _TKVECTOR_H_


namespace tkEngine{
	/*!
	 * @brief	ベクトル。
	 */
	class CVector3{
		D3DXVECTOR3 v;
	public:
		float& x() { return v.x; }
		float& y() { return v.y; }
		float& z() { return v.z; }
		const float& x() const { return v.x; }
		const float& y() const { return v.y; }
		const float& z() const { return v.z; }
		/*!
		 * @brief	ベクトルを加算。
		 */
		void Add(const CVector3& v) 
		{
			this->v += v.v;
		}
		void Add( const CVector3& v0, const CVector3& v1 )
		{
			this->v = v0.v + v1.v;
		}
		/*!
		 * @brief	ベクトルを減算。
		 */
		void Subtract( const CVector3& v )
		{
			this->v -= v.v;
		}
		void Subtract( const CVector3& v0, const CVector3& v1 )
		{
			this->v = v0.v - v1.v;
		}
		/*!
		 * @brief	内積。
		 */
		float Dot( const CVector3& v )
		{
			return D3DXVec3Dot(&this->v, &v.v);
		}
		/*!
		 * @brief	外積。
		 */
		void Cross(const CVector3& v)
		{
			D3DXVec3Cross(&this->v, &this->v, &v.v);
		}
		void Cross(const CVector3& v0, const CVector3& v1)
		{
			D3DXVec3Cross(&this->v, &v0.v, &v1.v);
		}
		/*!
		 * @brief	長さを取得
		 */
		float Length()
		{
			return D3DXVec3Length(&v);
		}
		/*!
		 * @brief	長さの二乗を取得
		 */
		float LengthSq()
		{
			return D3DXVec3Length(&v);
		}

	};
}
#endif // _TKVECTOR_H_