/*!
 * @brief	ŠÔ‘€ìŒn(ü‚è‚Ì‘¬“x‚ğ’x‚­)
 */

#pragma once

#include "Player/MagicSkill/IMagicSkill.h"

class MagicSkillSlow : public IMagicSkill{
	class MagicSkillStopFinish : public IGameObject {
		void Update() override;
	};
public:
	MagicSkillSlow(Player* pl);
	~MagicSkillSlow();
	void OnChangeMagic() override ;
	void OnStartMagic() override;
	void OnEndMagic() override;
	void OnUsingMagicSkill() override;
	float GetUseMP() const override
	{
		return 50.0f;
	}
private:
	MagicSkillStopFinish	m_finish;
};
