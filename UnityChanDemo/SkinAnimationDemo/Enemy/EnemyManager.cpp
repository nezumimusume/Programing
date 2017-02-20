#include "stdafx.h"
#include "Enemy/EnemyManager.h"
#include "Enemy/Enemy_00.h"

using namespace std;
namespace {
	struct SEnemyLocInfo {
		const char* modelName;		//モデル。
		CVector3	pos;			//座標。
		CQuaternion	rotation;		//回転。
	};
	SEnemyLocInfo enemyLocInfoTable[] = {
		#include "EnemyInfo.h"
		{NULL, CVector3::Zero, CQuaternion::Identity}
	};
}
EnemyManager::EnemyManager()
{
}
EnemyManager::~EnemyManager()
{
	for (auto& enemy : enemyList) {
		DeleteGO(enemy);
	}
}
bool EnemyManager::Start()
{
	//配置情報から敵を構築。
	map<const char*, vector<SEnemyLocInfo*>*> m;
	//同じ名前のモデルを集める。
	for (SEnemyLocInfo& info : enemyLocInfoTable) {
		if (info.modelName) {
			Enemy_00* enemy = NewGO<Enemy_00>(0);
			enemy->Init(info.modelName, info.pos, info.rotation);
			enemyList.push_back(enemy);
		}
	}
	return true;
}
void EnemyManager::SetFrameDeltaTimeMul(float mul)
{
	for (auto e : enemyList) {
		e->SetFrameDeltaTimeMul(mul);
	}
}
void EnemyManager::Update()
{
}
void EnemyManager::Render(CRenderContext& renderContext) 
{
}
