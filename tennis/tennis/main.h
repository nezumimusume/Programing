#pragma once
#include "court.h"
#include "Player.h"
#include "ball.h"

/*!
* @brief	ゲームクラス
*/
class Game : public IGameObject {
public:
	//コンストラクタ。
	Game();
	//デストラクタ。
	~Game();
	//Updateが呼ばれる前に一度だけ呼ばれる処理。
	void Start();
	//描画。
	void Render( CRenderContext& renderContext );
	//更新。
	void Update();
	//コートを取得。
	Court* GetCourt()
	{
		return &court;
	}
	//プレイヤーを取得。
	Player* GetPlayer()
	{
		return &player;
	}
private:
	Court court;
	Player player;
	Ball ball;
};
extern Game* game;