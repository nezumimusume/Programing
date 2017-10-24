#pragma once
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	CSkinModel skinModel;							//スキンモデル。
	CSkinModelData skinModelData;					//スキンモデルデータ。
	prefab::CDirectionLight* m_lig = nullptr;		//ライト。

};

