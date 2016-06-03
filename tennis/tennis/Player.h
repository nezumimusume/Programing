#pragma once

class Player {
public:
	Player();
	~Player();
	void Init();
	void Update();
	void Render( CRenderContext& renderContext );
	bool Player::IsHit(CVector3 pos);
private:
	CSkinModelData	modelData;		//モデルデータ。
	CSkinModel		model;			//モデル。
	CVector3		position;		//座標。
};