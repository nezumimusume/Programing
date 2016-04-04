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
	const CMatrix& mRot = m_sphere.GetRotationMatrix();
	
	m_pEffect->SetTechnique(renderContext, "ColorNormalPrimIuminance");
	m_pEffect->Begin(renderContext);
	m_pEffect->BeginPass(renderContext, 0);
	m_pEffect->SetValue(renderContext, "g_mWVP", &m_wvpMatrix, sizeof(m_wvpMatrix));
	m_pEffect->SetValue(renderContext, "g_worldRotationMatrix", &mRot, sizeof(mRot));
	m_pEffect->SetValue(
		renderContext,
		"g_light",
		&gm.GetFoodLight(),
		sizeof(CLight)
		);
	m_pEffect->CommitChanges(renderContext);
	m_sphere.Render(renderContext);

	m_pEffect->EndPass(renderContext);
	m_pEffect->End(renderContext);
}
void CFood::Build( f32 radius, const CVector3& pos )
{
	m_sphere.Create(radius, 10, 0xffffff55, true);
	m_pEffect = tkEngine::CEngine::Instance().EffectManager().LoadEffect("Assets/presetShader/ColorNormalPrim.fx");
	m_sphere.SetPosition(pos);
	m_sphere.UpdateWorldMatrix();
}