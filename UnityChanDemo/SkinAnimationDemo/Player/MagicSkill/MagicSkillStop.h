/*!
 * @brief	ŠÔ‘€ìŒn(ŠÔ’â~)
 */

#pragma once

#include "Player/MagicSkill/IMagicSkill.h"

class MagicSkillStop : public IMagicSkill{
	class MagicSkillStopFinish : public IGameObject {
		void Update() override;
	};
public:
	MagicSkillStop(Player* pl);
	~MagicSkillStop();
	void OnChangeMagic() override ;
	void OnStartMagic() override;
	void OnEndMagic() override;
	void OnUsingMagicSkill() override;
	float GetUseMP() const override
	{
		return 100.0f;
	}
private:
	MagicSkillStopFinish	m_finish;
};
