#pragma once
#include "Map/MapChip.h"
class Item;

class ItemMaker : public IGameObject
{
public:
	ItemMaker();
	~ItemMaker();

	void Init(const std::vector<SMapChipLocInfo*>& mapChipLocInfoList);

	bool Start() override;

	void Update() override;

	void NewItem(CVector3);

private:
	std::vector<SMapChipLocInfo*>		mapChipLocInfoList;		//アイテムの情報リスト
	std::vector<Item*>					itemList;				//アイテムの配列

};


extern ItemMaker *g_itemMaker;