/*!
 * @brief	プレイヤー
 */

#include "stdafx.h"
#include "Packman/game/Player/CPlayer.h"
#include "Packman/game/CGameManager.h"

/*!
 *@brief	Updateが初めて呼ばれる直前に一度だけ呼ばれる処理。
 */
void CPlayer::Start() 
{
}
/*!
*@brief	Update関数が実行される前に呼ばれる更新関数。
*/
void CPlayer::PreUpdate()
{
	Move();
}
/*!
 *@brief	更新処理。60fpsなら16ミリ秒に一度。30fpsなら32ミリ秒に一度呼ばれる。
 */
void CPlayer::Update() 
{
	m_sphere.SetPosition(m_position);
	m_sphere.UpdateWorldMatrix();
	CGameManager& gm = CGameManager::GetInstance();
	CMatrix mMVP = gm.GetGameCamera().GetViewProjectionMatrix();
	const CMatrix& mWorld = m_sphere.GetWorldMatrix();
	m_wvpMatrix.Mul(mWorld, mMVP);
	m_idMapModel.SetWVPMatrix(m_wvpMatrix);
	IDMap().Entry(&m_idMapModel);
	m_shadowModel.SetWorldMatrix(mWorld);
	ShadowMap().Entry(&m_shadowModel);
}
/*!
*@brief	移動処理。
*/
void CPlayer::Move()
{
	float moveSpeed = 0.02f;		//移動速度。
	if (KeyInput().IsPressA()) {
		moveSpeed *= 2.0f;			//キーボードのAが押されていたら速度を倍にする。
	}
	if (KeyInput().IsUpPress()) {
		m_position.z += moveSpeed;
	}
	if (KeyInput().IsDownPress()) {
		m_position.z -= moveSpeed;
	}
	if (KeyInput().IsRightPress()) {
		m_position.x += moveSpeed;
	}
	if (KeyInput().IsLeftPress()) {
		m_position.x -= moveSpeed;
	}
}
/*!
 *@brief	描画処理。60fpsなら16ミリ秒に一度。30fpsなら32ミリ秒に一度呼ばれる。
 */
void CPlayer::Render(tkEngine::CRenderContext& renderContext) 
{
	CGameManager& gm = CGameManager::GetInstance();
	m_sphere.RenderLightWVP(
		renderContext,
		m_wvpMatrix,
		gm.GetFoodLight(),
		false,
		true
	);
}
/*!
 *@brief	構築。
 *必ず先にCreateShapeを一度コールしておく必要がある。
 */
void CPlayer::Build( const CVector3& pos )
{
	m_sphere.Create(0.08f, 10, 0xffff0000, true );
	m_idMapModel.Create(m_sphere.GetPrimitive());
	m_shadowModel.Create(m_sphere.GetPrimitive());
	m_position = pos;
}