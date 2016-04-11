/*!
 * @brief	ínñ ÅB
 */

#include "stdafx.h"
#include "Packman/game/map/CGround.h"
#include "tkEngine/graphics/tkEffect.h"
#include "Packman/game/CGameManager.h"

void CGround::Create(f32 xz_size)
{
	m_box.Create(tkEngine::CVector3(xz_size*10, 1.0f, xz_size*10), 0x88888888, true);
	m_pEffect = tkEngine::CEngine::Instance().EffectManager().LoadEffect("Assets/presetShader/ColorNormalPrim.fx");
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
	CGameManager& gm = CGameManager::GetInstance();
	m_box.RenderLight(
		renderContext,
		gm.GetGameCamera().GetViewProjectionMatrix(),
		gm.GetGroundLight(),
		false
	);
}
	