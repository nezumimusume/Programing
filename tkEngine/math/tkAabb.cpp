/*!
 *@brief	AABB
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/math/tkAabb.h"

namespace tkEngine{
	/*!
	 *@brief	コンストラクタ。
	 */
	CAabb::CAabb()
	{
	}
	/*!
	 *@brief	初期化。
	 */
	void CAabb::Init(const CVector3& centerPosition, const CVector3& halfSize)
	{
		Update(centerPosition, halfSize);
	}
	/*!
	 *@brief	更新。
	 *@param[in]	centerPosition		中心座標。
	 */
	void CAabb::Update( const CVector3& centerPosition, const CVector3& halfSize)
	{
	}
}