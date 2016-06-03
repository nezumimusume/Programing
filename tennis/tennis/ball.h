#pragma once

class Ball {
public:
	Ball();
	~Ball();
	void Init();
	void Update();
	void Render(CRenderContext& renderContext);
public:
	CSkinModelData	modelData;		//モデルデータ。
	CSkinModel		model;			//モデル。
	CVector3		position;		//座標。
	CVector3		moveSpeed;		//移動速度。
};