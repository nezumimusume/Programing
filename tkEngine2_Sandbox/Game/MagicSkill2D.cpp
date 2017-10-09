/*!
 * @brief	現在使用可能なマジックスキルを表す2D
 */

#include "stdafx.h"
#include "HUD/MagicSkill2D.h"


MagicSkill2D::MagicSkill2D()
{
}
MagicSkill2D::~MagicSkill2D()
{
}
bool MagicSkill2D::Start()
{
	m_bgSprite.Init(TextureResources().Load("Assets/Sprite/SkillBG.png"));
	for (int i = 0; i < Player::eMagicSkillNum; i++) {
		char filePath[256];
		sprintf(filePath, "Assets/Sprite/skill0%d.png", i);
		m_magicSkillTexture[i] = TextureResources().Load(filePath);
	}
	m_skillSprite.Init(m_magicSkillTexture[g_player->GetCurrentMagicSkill()]);

	float half_w = Engine().GetFrameBufferWidth() / 2.0f;
	float half_h = Engine().GetFrameBufferHeight() / 2.0f;
	m_bgSprite.SetSize({ 90, 90 });
	m_skillSprite.SetSize({90, 90});
	m_bgSprite.SetPosition({ -half_w + 64, half_h - 64 });
	m_skillSprite.SetPosition({ -half_w + 64, half_h - 64 });
	m_skillSprite.SetAlpha(0.5f);
	
	return true;
}
void MagicSkill2D::Update()
{
	m_skillSprite.SetTexture(m_magicSkillTexture[g_player->GetCurrentMagicSkill()]);
}
void MagicSkill2D::PostRender(CRenderContext& renderContext)
{
	m_bgSprite.Draw(renderContext);
	m_skillSprite.Draw(renderContext);
}
