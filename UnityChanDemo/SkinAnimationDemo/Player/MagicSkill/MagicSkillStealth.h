/*!
 * @brief	ìßñæâªñÇñ@ÅB
 */

#pragma once

#include "Player/MagicSkill/IMagicSkill.h"

class MagicSkillStealth : public IMagicSkill{
public:
	MagicSkillStealth(Player* pl);
	~MagicSkillStealth();
	void OnChangeMagic() override ;
	void OnStartMagic() override;
	void OnEndMagic() override;
	void OnUsingMagicSkill() override;
	float GetUseMP() const override
	{
		return 50.0f;
	}
};