#pragma once

#include <iostream>

class Player{
public:
	Player();
	~Player();
	void Init();
	void Update();
	void Render( CRenderContext& renderContext );
	bool Player::IsHit(CVector3 pos);
	void Draw() {}
private:
	CSkinModelData	modelData;		//モデルデータ。
	CSkinModel		model;			//モデル。
	CVector3		position;		//座標。
};