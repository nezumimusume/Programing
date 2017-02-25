#pragma once

class MapChip;
class ItemMaker;

/*!
 * @brief	マップクラス。
 */
class Map : public IGameObject {
public:
	
	Map();
	~Map();
	bool Start() override;
	void Update() override;
	void Render(CRenderContext& renderContext) override;
private:

private:
	std::vector<MapChip*> mapChipList;	//マップチップのリスト。
};
