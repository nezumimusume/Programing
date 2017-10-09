/*!
 * @brief	現在使用可能なマジックスキルを表す2D
 */

#pragma once

#include "Player/Player.h"

/*!
 * @brief	現在使用可能なマジックスキルを表す2D
 */
class MagicSkill2D : public IGameObject{
public:
	MagicSkill2D();
	~MagicSkill2D();
	bool Start() override;
	void Update() override;
	void PostRender(CRenderContext& renderContext) override;
private:
	CSprite		m_bgSprite;		//!<背景スプライト。
	CSprite		m_skillSprite;	//!<スキルを表すスプライト。
	CTexture*	m_magicSkillTexture[Player::eMagicSkillNum];
};