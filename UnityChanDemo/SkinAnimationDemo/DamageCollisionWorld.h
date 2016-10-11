/*!
 * @brief	敵、プレイヤーにダメージを与えるコリジョンワールド。
 */

#pragma once

#include "tkEngine/shape/tkSphereShape.h"

#ifdef _DEBUG
#define DEBUG_DMG_COLLISION_DRAW
#else
#define DEBUG_DMG_COLLISION_DRAW
#endif
class DamageCollisionWorld : public IGameObject{
public:
	/*!
	* @brief	属性。
	*/
	enum EnAttr {
		enDamageToEnemy,		//敵にダメージを与えるコリジョン。
		enDamageToPlayer,		//プレイヤーにダメージを与えるコリジョン。
	};
	struct Collision {
		float radius;			//半径。
		CVector3 position;		//中心。
		float life;				//寿命。
		float damage;			//ダメージ量。
		EnAttr attr;			//属性。
		float time;
#ifdef DEBUG_DMG_COLLISION_DRAW
		CSphereShape debugShape;
#endif
	};
	
	/*!
	 * @brief	コンストラクタ。
	 */
	DamageCollisionWorld();
	/*!
	 * @brief	デストラクタ。
	 */
	~DamageCollisionWorld();
	/*!
	 * @brief	コリジョンを追加。
	 */
	void Add( 
		float radius, 
		const CVector3& pos, 
		float life, 
		float damage,
		EnAttr attr
	)
	{
		CollisionPtr colli = CollisionPtr(new Collision);
		colli->radius = radius;
		colli->position = pos;
		colli->life = life;
		colli->attr = attr;
		colli->time = 0.0f;
		colli->damage = damage;
		collisions.push_back(colli);
#ifdef DEBUG_DMG_COLLISION_DRAW
		colli->debugShape.Create(radius, 10, 0xFFFF0000, true);
#endif
	}
	void Start() override
	{

	}
	/*!
	 * @brief	更新。
	 */
	void Update() override;
	/*!
	*@brief	描画
	*/
	void Render(CRenderContext& renderContext) override;
	/*!
	*@brief	重なっているダメージコリジョンを取得する。
	*/
	const Collision* FindOverlappedDamageCollision(EnAttr attr, const CVector3& pos, float radius) const;
private:
	typedef std::shared_ptr<Collision> CollisionPtr;
	std::list<CollisionPtr>		collisions;
#ifdef DEBUG_DMG_COLLISION_DRAW
	CLight					light;
#endif

};

extern DamageCollisionWorld* g_damageCollisionWorld;