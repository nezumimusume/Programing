#pragma once

//テニスコート
class Court {
public:
	//コンストラクタ。
	Court();
	//デストラクタ。
	~Court();
	//初期化。
	void Init();
	//描画。
	void Render(CRenderContext& renderContext);
private:
	CSkinModelData	modelData;		//モデルデータ。
	CSkinModel		model;			//モデル。
};

const float COURT_MAX_X = 5.0f;		//コートのX座標の最大値。
const float COURT_MIN_X = -5.0f;	//コートのX座標の最小値。
const float COURT_MAX_Z = 3.0f;		//コートのZ座標の最大値。
const float COURT_MIN_Z = -3.0f;	//コートのZ座標の最小値。