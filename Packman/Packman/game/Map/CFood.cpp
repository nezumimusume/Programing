/*!
 * @brief	パックマンが食べるアイテム。
 */

#include "stdafx.h"
#include "Packman/game/map/CFood.h"
#include "tkEngine/graphics/tkEffect.h"
#include "Packman/game/CGameManager.h"

void CFood::Start()
{
}
void CFood::Update()
{
	CGameManager& gm = CGameManager::GetInstance();
	CMatrix mMVP = gm.GetGameCamera().GetViewProjectionMatrix();
	const CMatrix& mWorld = m_sphere.GetWorldMatrix();
	m_wvpMatrix.Mul(mWorld, mMVP);
	CEngine::Instance().IDMap().Entry(&m_idMapModel);
}
void CFood::Render(tkEngine::CRenderContext& renderContext)
{
	CGameManager& gm = CGameManager::GetInstance();

	m_sphere.RenderLight(
		renderContext,
		gm.GetGameCamera().GetViewProjectionMatrix(),
		gm.GetFoodLight(),
		true
	);
}
void CFood::Build( f32 radius, const CVector3& pos )
{
	m_sphere.Create(radius, 10, 0xffffff55, true);
	m_sphere.SetPosition(pos);
	m_sphere.UpdateWorldMatrix();
}