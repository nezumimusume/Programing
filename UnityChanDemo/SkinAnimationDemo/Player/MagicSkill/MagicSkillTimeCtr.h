/*!
 * @brief	éûä‘ëÄçÏån
 */

#pragma once

#include "Player/MagicSkill/IMagicSkill.h"

namespace tkEngine{
	class IPostEffectFilter;
}

class MagicSkillTimeCtr : public IMagicSkill{
	class Finish : public IGameObject {
		IPostEffectFilter& postEffectFilter;
	public:
		Finish(IPostEffectFilter& _postEffectFilter) : 
			postEffectFilter(_postEffectFilter)
		{}
		void Update() override;
	};
public:
	MagicSkillTimeCtr(Player* pl, IPostEffectFilter& filter, float mulDeltaTime, float useMp);
	~MagicSkillTimeCtr();
	void OnChangeMagic() override ;
	void OnStartMagic() override;
	void OnEndMagic() override;
	void OnUsingMagicSkill() override;
	float GetUseMP() const override
	{
		return useMp;
	}
private:
	Finish					finish;
	IPostEffectFilter&		postEffectFilter;
	float 					mulDeltaTime = 0.0f;
	float					useMp = 0.0f;
};
