#pragma once
/*
回復アイテムクラス
*/
class Item : public IGameObject
{
public:
	Item();
	~Item();
	bool Start() override;
	void Update() override;
	void Render(CRenderContext&) override;

private:
	CSkinModel		skinModel;
	CSkinModelData	skinModelData;
	CVector3		position;
	CQuaternion		rotation;
	CLight			light;


};

