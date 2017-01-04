/*!
 * @brief	高速移動魔法。
 */

#include "stdafx.h"
#include "Player/MagicSkill/MagicSkillDash.h"
#include "Player/Player.h"

MagicSkillDash::MagicSkillDash(Player* pl) :
	IMagicSkill(pl)
{
}
MagicSkillDash::~MagicSkillDash()
{
}
void MagicSkillDash::OnChangeMagic()
{

}
void MagicSkillDash::OnStartMagic()
{
	g_camera->SetViewAngle(CMath::DegToRad(60.0f));
	g_camera->SetDampingRate(0.9f);
	MotionBlur().SetEnable(true);
}
void MagicSkillDash::OnEndMagic()
{
	g_camera->SetViewAngle(CMath::DegToRad(70.0f));
	g_camera->SetDampingRate(0.9f);
	MotionBlur().SetEnable(false);
}
void MagicSkillDash::OnUsingMagicSkill()
{
	//プレイヤーの内部時間を1.4倍速。
	player->SetLocalFrameDeltaTime(player->GetLocalFrameDeltaTime() * 1.7f);
}


