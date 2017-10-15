#pragma once
class Player : public IGameObject
{
public:
	////////////////////////////////////////////
	//メンバ関数。
	////////////////////////////////////////////
	Player();
	~Player();
	/*!
	*@brief	Updateの直前で呼ばれる開始処理。
	*@details
	* 本関数がtrueを返すとゲームオブジェクトの準備が完了したと判断されて</br>
	* Update関数が呼ばれ出します。trueを返して以降はStart関数は呼ばれなくなります。</br>
	* ゲームオブジェクトの初期化に複数フレームかかる場合などはfalseを返して、初期化ステップなどを使って</br>
	* 適切に初期化を行ってください。
	*/
	bool Start();
	/*!
	*@brief	更新。
	*/
	void Update();
	/*!
	*@brief	描画。
	*/
	void Render(CRenderContext& rc);
	////////////////////////////////////////////
	//メンバ変数。
	////////////////////////////////////////////
	CSkinModel m_skinModel;			//キャラクタスキンモデル。
	CSkinModelData m_skinModelData;	//スキンモデルデータ。
};

