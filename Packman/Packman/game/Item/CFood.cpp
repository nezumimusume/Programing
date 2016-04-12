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
	const CMatrix& mWorld = m_sphere->GetWorldMatrix();
	m_wvpMatrix.Mul(mWorld, mMVP);
	CEngine::Instance().IDMap().Entry(&m_idMapModel);
}
void CFood::Render(tkEngine::CRenderContext& renderContext)
{
	CGameManager& gm = CGameManager::GetInstance();

	m_sphere->RenderLightWVP(
		renderContext,
		m_wvpMatrix,
		gm.GetFoodLight(),
		true
	);
}
void CFood::Build( f32 radius, const CVector3& pos )
{
	if(m_sphere == nullptr){
		m_sphere = new tkEngine::CSphereShape();
		m_sphere->Create(radius, 10, 0xffffff55, true);
	}
	m_position = pos;
}