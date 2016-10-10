/*!
 * @brief	敵、プレイヤーにダメージを与えるコリジョンワールド。
 */

#include "stdafx.h"
#include "DamageCollisionWorld.h"

DamageCollisionWorld::DamageCollisionWorld()
{
}

DamageCollisionWorld::~DamageCollisionWorld()
{
}
void DamageCollisionWorld::Update()
{
	std::list<Collision>::iterator it = collisions.begin();
	while(it != collisions.end()){
		it->time += GameTime().GetFrameDeltaTime();
		if(it->time > it->life){
			//死亡。
			it = collisions.erase(it);
		}else{
			it++;
		}
	}
}