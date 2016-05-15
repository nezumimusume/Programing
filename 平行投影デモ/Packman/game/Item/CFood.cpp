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
		m_sphere->Create(radius, 10, 0xffffff55, true);
	}
}
void CFood::ReleaseShape()
{
	delete m_sphere;
	m_sphere = nullptr;
}