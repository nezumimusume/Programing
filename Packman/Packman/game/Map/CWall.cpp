/*!
 * @brief	��
 */

#include "stdafx.h"
#include "Packman/game/map/CWall.h"
#include "tkEngine/graphics/tkEffect.h"
#include "Packman/game/CGameManager.h"

void CWall::Start()
{
}
void CWall::Update()
{
	CGameManager& gm = CGameManager::GetInstance();
	CMatrix mMVP = gm.GetGameCamera().GetViewProjectionMatrix();
	const CMatrix& mWorld = m_box.GetWorldMatrix();
	m_wvpMatrix.Mul(mWorld, mMVP);
	m_idMapModel.SetWVPMatrix(m_wvpMatrix);
	CEngine::Instance().IDMap().Entry(&m_idMapModel);
	CEngine::Instance().ShadowMap().Entry(&m_shadowModel);
	m_shadowModel.SetWorldMatrix(mWorld);
}
void CWall::Render(tkEngine::CRenderContext& renderContext)
{
	CGameManager& gm = CGameManager::GetInstance();
	m_box.RenderLight(
		renderContext,
		gm.GetGameCamera().GetViewProjectionMatrix(),
		gm.GetWallLight(),
		false
	);
}
void CWall::Build( const CVector3& size, const CVector3& pos )
{
	m_box.Create( size, 0xffff0000, true );
	m_pEffect = tkEngine::CEngine::Instance().EffectManager().LoadEffect("Assets/presetShader/ColorNormalPrim.fx");
	m_box.SetPosition(pos);
	m_box.UpdateWorldMatrix();
	m_idMapModel.Create(m_box.GetPrimitive());
	m_shadowModel.Create(m_box.GetPrimitive());
}
	