#pragma once
class Background : public IGameObject
{
public:
	Background();
	~Background();
	bool Start() override;
	void Update() override;
	void Render(CRenderContext& rc) override;
private:
	CSkinModelData		m_skinModelData;	//!<スキンモデルデータ。
	CSkinModel			m_skinModel;		//!<スキンモデル。
	CShaderResourceView	m_normalMapSRV;		//!<法線マップのSRV。
};

