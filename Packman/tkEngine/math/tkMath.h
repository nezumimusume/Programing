/*!
 * @brief	数学関係色々。
 */

#ifndef _TK_MATH_H_
#define _TK_MATH_H_

namespace tkEngine{
	class CMath{
	public:
		static const f32 PI;
		/*!
		 * @brief	degreeからradianに変換。
		 */
		static f32 DegToRad( f32 deg )
		{
			return deg * (PI/180.0f);
		}
		/*!
		 * @brief	radianからdegreeに変換。
		 */
		static f32 RadToDeg( f32 rad )
		{
			return rad / (PI/180.0f);
		}
	};
}

#endif //_TK_MATH_H_