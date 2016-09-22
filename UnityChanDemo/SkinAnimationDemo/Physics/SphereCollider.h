/*!
 * @brief	球体コライダー。
 */

#pragma once

#include "Physics/ICollider.h"

class SphereCollider : public ICollider
{
public:
	/*!
	 * @brief	コンストラクタ。
	 */
	SphereCollider();
	/*!
	 * @brief	デストラクタ。
	 */
	~SphereCollider();
	/*!
	 * @brief	球体コライダーを作成。
	 */
	void Create( const float radius );
	btCollisionShape* GetBody() override
	{
		return shape;
	}
private:
	btSphereShape*		shape;
};