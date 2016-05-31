/*!
 * @brief	パックマンが食べるアイテム。
 */

#include "stdafx.h"
#include "Packman/game/item/CFood.h"
#include "tkEngine/graphics/tkEffect.h"
#include "Packman/game/CGameManager.h"

CSphereShape*	CFood::m_sphere = nullptr;
void CFood::Awake()
{
	m_position = CVector3::Zero;
}
void CFood::Start()
{
}
void CFood::Update()
{
	m_sphere->SetPosition(m_position);
	m_sphere->UpdateWorldMatrix();
	CGameManager& gm = CGameManager::GetInstance();
	CMatrix mMVP = gm.GetGameCamera().GetViewProjectionMatrix();
	m_worldMatrix = m_sphere->GetWorldMatrix();
	m_wvpMatrix.Mul(m_worldMatrix, mMVP);
	m_idMapModel.SetWVPMatrix(m_wvpMatrix);
	IDMap().Entry(&m_idMapModel);
	//プレイヤーから敵までのベクトルを計算する。
	CVector3 diff;
	CVector3 playerPos = Player().GetPosition();
	diff.x = playerPos.x - m_position.x;
	diff.y = playerPos.y - m_position.y;
	diff.z = playerPos.z - m_position.z;
	//プレイヤーから敵までのベクトルを大きさ１のベクトルに変換する。
	//このようなベクトルを向きベクトルという。大きさを持たないベクトル。
	//大きさを持たないベクトルはベクトルの長さで各要素を除算すると求まる。
	float L = diff.Length();
	diff.x /= L;
	diff.y /= L;
	diff.z /= L;
	//後は移動速度を設定して、この向きベクトルの方向に敵を動かす。
	//移動速度は0.05くらいにしてみる。
	m_position.x += diff.x * 0.05f;
	m_position.y += diff.y * 0.05f;
	m_position.z += diff.z * 0.05f;
}
void CFood::Render(tkEngine::CRenderContext& renderContext)
{
	CGameManager& gm = CGameManager::GetInstance();
	m_sphere->RenderLightWVP(
		renderContext,
		m_wvpMatrix,
		gm.GetFoodLight(),
		true,
		true,
		&m_worldMatrix
	);
}
void CFood::Build( const CVector3& pos )
{
	m_idMapModel.Create(m_sphere->GetPrimitive());
	m_position = pos;
}
void CFood::CreateShape(float radius)
{
	if (m_sphere == nullptr) {
		m_sphere = new tkEngine::CSphereShape();
		m_sphere->Create(radius * 1.5f, 10, 0xffffffff, true);
	}
}
void CFood::ReleaseShape()
{
	delete m_sphere;
	m_sphere = nullptr;
}