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
	public:
		union{
			struct { float x, y, z; };
			float v[3];
		};
		static const CVector3 Zero;
		static const CVector3 Right;
		static const CVector3 Left;
		static const CVector3 Up;
		static const CVector3 Down;
		static const CVector3 Front;
		static const CVector3 Back;
		static const CVector3 AxisX;
		static const CVector3 AxisY;
		static const CVector3 AxisZ;
	public:
		operator D3DXVECTOR3(void) { return s_cast<D3DXVECTOR3>(*this); }
		CVector3() {}
		/*!
		* @brief	コンストラクタ。
		*/
		CVector3(f32 x, f32 y, f32 z)
		{
			Set(x, y, z);
		}
		/*!
		* @brief	ベクトルの各要素を設定。
		*/
		void Set(f32 x, f32 y, f32 z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}
		/*!
		 * @brief	ベクトルを加算。
		 */
		void Add(const CVector3& v) 
		{
			x += v.x;
			y += v.y;
			z += v.z;
		}
		void Add( const CVector3& v0, const CVector3& v1 )
		{
			x = v0.x + v1.x;
			y = v0.y + v1.y;
			z = v0.z + v1.z;
		}
		/*!
		 * @brief	ベクトルを減算。
		 */
		void Subtract( const CVector3& v )
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}
		void Subtract( const CVector3& v0, const CVector3& v1 )
		{
			x = v0.x - v1.x;
			y = v0.y - v1.y;
			z = v0.z - v1.z;
		}
		/*!
		 * @brief	内積。
		 */
		f32 Dot( const CVector3& v )
		{
			return x * v.x + y * v.y + z * v.z;
		}
		/*!
		 * @brief	外積。
		 */
		void Cross(const CVector3& v)
		{
			f32 _x = ( x * v.z ) - ( v.y * z );
			f32 _y = ( z * v.x ) - ( v.z * x );
			f32 _z = ( x * v.y ) - ( v.x * y );
			x = _x;
			y = _y;
			z = _z;
		}
		void Cross(const CVector3& v0, const CVector3& v1)
		{
			f32 _x = ( v0.y * v1.z ) - ( v1.y * v0.z );
			f32 _y = ( v0.z * v1.x ) - ( v1.z * v0.x );
			f32 _z = ( v0.x * v1.y ) - ( v1.x * v0.y );
			x = _x;
			y = _y;
			z = _z;
		}
		/*!
		 * @brief	長さを取得
		 */
		float Length()
		{
			return sqrt(LengthSq());
		}
		/*!
		 * @brief	長さの二乗を取得
		 */
		float LengthSq()
		{
			return x * x + y * y + z * z;
		}
		/*!
		* @brief	拡大。
		*/
		void Scale(f32 s)
		{
			x *= s;
			y *= s;
			z *= s;
		}
		/*!
		* @brief	法線を正規化。
		*/
		void Normalize()
		{
			f32 len = Length();
			TK_ASSERT( len > 0.0f, "zero vector!!!");
			x /= len;
			y /= len;
			z /= len;
		}
		/*!
		* @brief	除算。
		*/
		void Div(f32 d)
		{
			x /= d;
			y /= d;
			z /= d;
		}
	};
	/*!
	 *@brief	4要素のベクトルクラス。
	 */
	class CVector4{
	public:
		union{
			struct { float x, y, z, w; };
			float v[4];
		};
	public:
		operator D3DXVECTOR4( void ) { return s_cast<D3DXVECTOR4>(*this); }
		CVector4(){}
		/*!
		 *@brief	コンストラクタ
		 */
		CVector4(f32 x, f32 y, f32 z, f32 w)
		{
			Set(x, y, z, w);
		}
		/*!
		 *@brief	ベクトルの各要素を設定。
		 */
		void Set(f32 x, f32 y, f32 z, f32 w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}
		/*!
		 *@brief	ベクトルを加算。
		 */
		void Add( const CVector4& v )
		{
			x += v.x;
			y += v.y;
			z += v.z;
			w += v.w;
		}
		void Add( const CVector4& v0, const CVector4& v1 )
		{
			x = v0.x + v1.x;
			y = v0.y + v1.y;
			z = v0.z + v1.z;
			w = v0.w + v1.w;
		}
		/*!
		 *@brief	ベクトルを減算。
		 */
		void Subtract( const CVector4& v )
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}
		void Subtract( const CVector4& v0, const CVector4& v1 )
		{
			x = v0.x - v1.x;
			y = v0.y - v1.y;
			z = v0.z - v1.z;
			w = v0.w - v1.w;
		}
		/*!
		 *@brief	内積
		 */
		f32 Dot( const CVector4& v )
		{
			return x * v.x + y * v.y + z * v.z + w * v.w;
		}
		/*!
		 * @brief	長さを取得
		 */
		float Length()
		{
			return sqrt(LengthSq());
		}
		/*!
		 * @brief	長さの二乗を取得
		 */
		float LengthSq()
		{
			return x * x + y * y + z * z + w * w;
		}
		/*!
		* @brief	拡大。
		*/
		void Scale(f32 s)
		{
			x *= s;
			y *= s;
			z *= s;
			w *= s;
		}
	};
	
	class CQuaternion : public CVector4{
	public:
		/*!
		 *@brief	任意の軸周りの回転クォータニオンを作成。
		 */
		void SetRotation( const CVector3& axis, f32 angle )
		{
			f32 s;
			f32 halfAngle = angle * 0.5f;
			s = sin(halfAngle);
			w = cos(halfAngle);
			x = axis.x * s;
			y = axis.y * s;
			z = axis.z * s;
		}
	};
}
#endif // _TKVECTOR_H_