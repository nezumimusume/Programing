#pragma once
class Game : public IGameObject
{
public:
	/////////////////////////////////////////////
	//メンバ関数。
	/////////////////////////////////////////////
	Game();
	~Game();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	/*!
	*@brief	Render関数が実行された後で呼ばれる描画処理
	*@details
	* ポストエフェクトの後で実行されます。HUDなどポストエフェクトの影響を受けたくない描画物はここでレンダリングしてください。
	*/
	void PostRender(CRenderContext& rc);
	/////////////////////////////////////////////
	//メンバ変数とか。
	/////////////////////////////////////////////
	CSkinModel m_skinModel;			//スキンモデル。
	CSkinModelData m_skinModelData;	//スキンモデルデータ。
	CSprite m_sprite;				//スプライト。
	CShaderResourceView m_texture;	//テクスチャ。
};

