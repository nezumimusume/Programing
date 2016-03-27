/*!
 * @brief	クォータニオン
 */
#ifndef _TKQUATERNION_H_
#define _TKQUATERNION_H_

namespace tkEngine{
	class CQuaternion{
	public:
		union{
			struct { float x, y, z, w; };
			float v[4];
		};
	public:
	};
}
#endif //_TKQUATERNION_H_