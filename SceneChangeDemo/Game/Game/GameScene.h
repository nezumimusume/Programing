/*!
 *@brief	ゲームシーン。
 */
#pragma once

/*!
 *@brief	ゲームシーン。
 */
class GameScene : public IGameObject{
public:
	/*!
	 *@brief	コンストラクタ。
	 */
	GameScene();
	/*!
	 *@brief	デストラクタ。
	 */
	~GameScene();
	/*!
	 *@brief	開始処理。
	 */
	bool Start() ;
	/*!
	 *@brief	更新処理。
	 */
	void Update();
private:
	CSoundSource* bgmSource;
};