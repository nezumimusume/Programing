#include "stdafx.h"
#include "EnemyManager.h"

using namespace std;
namespace {
	struct SEnemyLocInfo {
		const char* modelName;		//モデル。
		CVector3	pos;			//座標。
		CQuaternion	rotation;		//回転。
	};
	SEnemyLocInfo enemyLocInfoTable[] = {
		#include "EnemyInfo.h"
	};
}
EnemyManager::EnemyManager()
{
}
EnemyManager::~EnemyManager()
{
}
void EnemyManager::Start()
{
	//配置情報から敵を構築。
	map<const char*, vector<SEnemyLocInfo*>*> m;
	//同じ名前のモデルを集める。
	for (SEnemyLocInfo& info : enemyLocInfoTable) {
		auto& it = m.find(info.modelName);
		if (it != m.end()) {
			//この名前のモデルは登録済み。
			it->second->push_back(&info);
		}
		else {
			//新規モデル。
			vector<SEnemyLocInfo*>* newList = new vector<SEnemyLocInfo*>();
			newList->push_back(&info);
			m.insert(std::pair< const char*, vector<SEnemyLocInfo*>*>(
				info.modelName,
				newList
				));
		}
	}
	
	for (auto& enemyList : m) {
		//まずモデルをロードする。
		
	}

}
void EnemyManager::Update()
{
}
void EnemyManager::Render(CRenderContext& renderContext) 
{
}
