/*!
 * @brief	マジックスキル
 */

#include "stdafx.h"
#include "Player/MagicSkill/IMagicSkill.h"
#include "Player/Player.h"


/*!
 * @brief	更新。
 */
void IMagicSkill::Update()
{
	if (Pad(0).IsPress(enButtonRB2)) {
		//MPの残量を見て魔法を使えるか調べる。
		float useMp = GetUseMP() * GameTime().GetFrameDeltaTime();
		if (player->GetMP() - useMp >= 0.0f) {
			if (!isUsingMagicSkill) {
				//魔法使用開始。
				OnStartMagic();
				isUsingMagicSkill = true;
			}
			OnUsingMagicSkill();
		}
		else {
			//魔法使えなかった。
			OnEndMagic();
			isUsingMagicSkill = false;
		}
		player->UseMagicPoint(useMp);
	}
	else if (isUsingMagicSkill) {
		//魔法使用終了。
		OnEndMagic();
		isUsingMagicSkill = false;
	}
}
