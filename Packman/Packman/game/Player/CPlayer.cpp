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
	m_position = CVector3::Zero;
}
/*!
 *@brief	更新処理。60fpsなら16ミリ秒に一度。30fpsなら32ミリ秒に一度呼ばれる。
 */
void CPlayer::Update() 
{
	Move();
	m_sphere.SetPosition(m_position);
	m_sphere.UpdateWorldMatrix();
	CGameManager& gm = CGameManager::GetInstance();
	CMatrix mMVP = gm.GetGameCamera().GetViewProjectionMatrix();
	const CMatrix& mWorld = m_sphere.GetWorldMatrix();
	m_wvpMatrix.Mul(mWorld, mMVP);

}
/*!
*@brief	移動処理。
*/
void CPlayer::Move()
{
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
		true,
		true
	);
}
/*!
 *@brief	構築。
 *必ず先にCreateShapeを一度コールしておく必要がある。
 */
void CPlayer::Build( const CVector3& pos )
{
	m_sphere.Create(0.1f, 10, 0xffff0000, true );
}