#include "stdafx.h"
#include "ItemMaker.h"
#include "Scene/GameScene.h"
#include "Item.h"

ItemMaker *g_itemMaker;

ItemMaker::ItemMaker()
{
}


ItemMaker::~ItemMaker()
{
	for (auto& item : itemList)
	{
		DeleteGO(item);
	}
}

void ItemMaker::Init(const std::vector<SMapChipLocInfo*>& mapChipLocInfoList)
{
	this->mapChipLocInfoList = mapChipLocInfoList;
}

bool ItemMaker::Start()
{
	//モデルデータがロードされていればアイテムを生成する
	if (gameScene->GetItemModelData() != nullptr)
	{
		for (auto& mapChipLocInfo : mapChipLocInfoList)
		{
			Item *item = NewGO<Item>(0);
			item->Init(mapChipLocInfo->pos);
			itemList.push_back(item);
		}
		return true;
	}
	return false;
}

void ItemMaker::NewItem(CVector3 position)
{
	Item *item = NewGO<Item>(0);
	item->Init(position);
	itemList.push_back(item);
}

void ItemMaker::Update()
{
	//アイテムの消去処理
	for (int i = 0;i < itemList.size(); i++)
	{
		if (itemList[i]->IsDelete())
		{
			DeleteGO(itemList[i]);
			itemList.erase(itemList.begin() + i);
		}
	}
}