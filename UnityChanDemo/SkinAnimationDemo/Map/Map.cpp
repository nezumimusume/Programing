#include "stdafx.h"
#include "Map/Map.h"
#include "Map/MapChip.h"

using namespace std;
namespace {
	//マップチップの配置情報のテーブル。
	SMapChipLocInfo mapChipLocInfoTable[] = {
		#include "locationInfo.h"
	};
}
Map::Map()
{

}
Map::~Map()
{
	for (auto& mapchip : mapChipList) {
		DeleteGO(mapchip);
	}
}

#define ENABLE_MAPCHIP_INSTANCING

bool Map::Start()
{
	//配置情報からマップを構築
	int tableSize = sizeof(mapChipLocInfoTable)/sizeof(mapChipLocInfoTable[0]);
#ifdef ENABLE_MAPCHIP_INSTANCING
	map<int , vector<SMapChipLocInfo*>*> m;
	//インスタンシング描画を行うために、同じ名前のモデルを集める。
	for(int i = 0; i < tableSize; i++){
		int hash = CUtil::MakeHash(mapChipLocInfoTable[i].modelName);
		auto& it = m.find(hash);
		if (it != m.end()) {
			//この名前のモデルは登録済み
			it->second->push_back(&mapChipLocInfoTable[i]);
		}
		else {
			//新規
			vector<SMapChipLocInfo*>* newList = new vector<SMapChipLocInfo*>;
			newList->push_back(&mapChipLocInfoTable[i]);
			m.insert(std::pair< int, vector<SMapChipLocInfo*>*>(
				hash,
				newList
			));
		}
	}
	for (auto& mapchipList : m) {
		//マップチップを生成
		MapChip* mapChip = NewGO<MapChip>(0);
		mapChip->Init(*mapchipList.second);
		mapChipList.push_back(mapChip);
		delete mapchipList.second;
	}
#else
	//インスタンシングを使わないバージョン。
	for (int i = 0; i < tableSize; i++) {
		vector<SMapChipLocInfo*> list;
		list.push_back(&mapChipLocInfoTable[i]);
		MapChip* mapChip = NewGO<MapChip>(0);
		mapChip->Init(list);
		mapChipList.push_back(mapChip);
	}
#endif
	return true;
}
void Map::Update()
{
}
void Map::Render(CRenderContext& renderContext)
{
}