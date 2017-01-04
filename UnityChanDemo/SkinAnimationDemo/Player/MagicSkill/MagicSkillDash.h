/*!
 * @brief	‚‘¬ˆÚ“®–‚–@B
 */

#pragma once

#include "Player/MagicSkill/IMagicSkill.h"

class MagicSkillDash : public IMagicSkill{
public:
	MagicSkillDash(Player* pl);
	~MagicSkillDash();
	void OnChangeMagic() override ;
	void OnStartMagic() override;
	void OnEndMagic() override;
	void OnUsingMagicSkill() override;
	float GetUseMP() const override
	{
		return 50.0f;
	}
};

