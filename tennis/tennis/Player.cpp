#include "stdafx.h"
#include "player.h"
#include "GameCamera.h"

const float PLAYER_HALF_SIZE_X = 0.1f;	//プレイヤーのX方向の半分のサイズ。
const float PLAYER_HALF_SIZE_Z = 1.0f;	//プレイヤーのZ方向の半分のサイズ。


Player::Player()
{
	position = CVector3(-4.3f, 0.5f, 0.0f);
}
Player::~Player()
{
}
void Player::Init()
{
	//モデルデータのロード。
	modelData.LoadModelData("Assets/modelData/player.x", NULL);
	//モデルにモデルデータをセット。
	model.Init(&modelData);
}
void Player::Update()
{
	CVector3 nextPos = position;
	bool isPossibleMove = true;
	//移動処理。
	if (KeyInput().IsUpPress()) {
		nextPos.z += 0.1f;
	}
	if (KeyInput().IsDownPress()) {
		nextPos.z -= 0.1f;
	}
	if (KeyInput().IsLeftPress()) {
		nextPos.x -= 0.1f;
	}
	 if (KeyInput().IsRightPress()) {
		nextPos.x += 0.1f;
	}
	if (nextPos.x >= 0.0f) {
		//コートの右半分に移動しようとしている。
		isPossibleMove = false;
	}
	if (isPossibleMove) {
		position = nextPos;
	}
	//ワールド行列を更新。
	model.UpdateWorldMatrix(position, CQuaternion::Identity, CVector3::One);
}
bool Player::IsHit(CVector3 pos)
{
	if (pos.x > position.x - PLAYER_HALF_SIZE_X
		&& pos.x < position.x + PLAYER_HALF_SIZE_X
		&&pos.z > position.z - PLAYER_HALF_SIZE_Z
		&& pos.z < position.z + PLAYER_HALF_SIZE_Z
		) {
		//当たっている。
		return true;
	}
	return false;
}
void Player::Render( CRenderContext& renderContext )
{
	//描画。
	model.Draw(renderContext, gameCamera->GetViewMatrix(), gameCamera->GetProjectionMatrix());
}