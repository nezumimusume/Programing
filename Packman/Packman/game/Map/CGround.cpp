/*!
 * @brief	’n–ÊB
 */

#include "stdafx.h"
#include "Packman/game/map/CGround.h"
#include "tkEngine/graphics/tkEffect.h"
#include "Packman/game/CGameManager.h"

void CGround::Create(float xz_size)
{
	m_box.Create(tkEngine::CVector3(xz_size*10, 1.0f, xz_size*10), 0x88888888, true);
	m_pEffect = tkEngine::EffectManager().LoadEffect("Assets/presetShader/ColorNormalPrim.fx");
}
void CGround::Start()
{
}
void CGround::Update()
{
	CVector3 pos;
	pos.Set(0.0f, -0.5f, 0.0f);
	m_box.SetPosition(pos);
	m_box.UpdateWorldMatrix();
}
void CGround::Render(tkEngine::CRenderContext& renderContext)
{
#if 1
	CGameManager& gm = CGameManager::GetInstance();
	CMatrix mMVP = gm.GetGameCamera().GetViewProjectionMatrix();
	const CMatrix& mWorld = m_box.GetWorldMatrix();
	mMVP.Mul(mWorld, mMVP);
	m_box.RenderLightWVP(
		renderContext,
		mMVP,
		gm.GetGroundLight(),
		false,
		true
		);
#else
	CGameManager& gm = CGameManager::GetInstance();
	CMatrix mMVP = gm.GetGameCamera().GetViewProjectionMatrix();
	const CMatrix& mWorld = m_box.GetWorldMatrix();
	const CShadowMap& shadowMap = CEngine::Instance().ShadowMap();
	const CMatrix& mLVP = shadowMap.GetLVPMatrix();
	mMVP.Mul(mWorld, mMVP);
	CMatrix mRot = m_box.GetRotationMatrix();
	float farNear[] = {
		shadowMap.GetFar(),
		shadowMap.GetNear()
	};
	m_pEffect->SetTechnique(renderContext, "ColorNormalShadowPrim");
	m_pEffect->Begin(renderContext);
	m_pEffect->BeginPass(renderContext, 0);
	m_pEffect->SetValue(renderContext, "g_mWVP", &mMVP, sizeof(mMVP));
	m_pEffect->SetValue(renderContext, "g_worldRotationMatrix", &mRot, sizeof(mRot));
	m_pEffect->SetValue(renderContext, "g_mWorld", &mWorld, sizeof(mWorld));
	m_pEffect->SetValue(renderContext, "g_mLVP", &mLVP, sizeof(mLVP));
	m_pEffect->SetValue(renderContext, "g_farNear", farNear, sizeof(farNear));
	m_pEffect->SetValue(
		renderContext,
		"g_light",
		&gm.GetGroundLight(),
		sizeof(CLight)
		);
	m_pEffect->SetTexture(renderContext, "g_shadowMap", CEngine::Instance().ShadowMap().GetTexture());
	m_pEffect->CommitChanges(renderContext);
	m_box.Render(renderContext);

	m_pEffect->EndPass(renderContext);
	m_pEffect->End(renderContext);
#endif//
}
	