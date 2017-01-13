/*!
 * @brief	“§–¾‰»–‚–@B
 */

#include "stdafx.h"
#include "Player/MagicSkill/MagicSkillStealth.h"
#include "Player/player.h"

MagicSkillStealth::MagicSkillStealth(Player* pl) :
	IMagicSkill(pl)
{
}
MagicSkillStealth::~MagicSkillStealth()
{
}
void MagicSkillStealth::OnChangeMagic()
{
}
void MagicSkillStealth::OnStartMagic()
{
	player->SetStealthFlag(true);
}
void MagicSkillStealth::OnEndMagic() 
{
	player->SetStealthFlag(false);
}
void MagicSkillStealth::OnUsingMagicSkill() 
{
}

