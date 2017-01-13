/*!
 * @brief	カード選択演出。
 */

#include "stdafx.h"
#include "CardSelectPerfomance.h"
#include "Common/Card.h"

CardSelectPerfomance::CardSelectPerfomance()
{
}
CardSelectPerfomance::~CardSelectPerfomance()
{
}
/*!
* @brief	初期化。
*@param[in]	playerNo		プレイヤー番号。
*@param[in]	selectCard		選択したカード。
*@param[in]	multiplyCard	重複カード。ない場合はNULL。
*/
void CardSelectPerfomance::Init(int playerNo, Card* selectCard, Card* multiplyCard)
{
	this->playerNo = playerNo;
	this->selectCard = selectCard;
	this->multiplyCard = multiplyCard;
	timer = 0.0f;
	execStep = enExecStep_PickupSelectCard;
}
bool CardSelectPerfomance::Start()
{
	return true;
}
void CardSelectPerfomance::Update()
{
	timer += GameTime().GetFrameDeltaTime();
	switch (execStep) {
	case enExecStep_PickupSelectCard: {
		if (timer < 0.5f) {
			CVector3 pos = selectCard->GetPosition();
			pos.z -= 2.0f;
			if (playerNo == 0) {
				pos.y -= 3.0f;
			}
			else {
				pos.y += 3.0f;
			}
			selectCard->SetPosition(pos);
		}
		else {
			timer = 0.0f;
			execStep = enExecStep_RotateSelectCard;
		}
	}break;
	case enExecStep_RotateSelectCard: {
		if (playerNo == 1) {
			//COMのときはいらない。
			execStep = enExecStep_PickupMultiplyCard;
		}
		else {
			float t = min(1.0f, timer / 0.5f);
			float angle = CMath::PI + (CMath::PI * 2.0f - CMath::PI) * t;
			CQuaternion rot;
			rot.SetRotation(CVector3::AxisY, angle);
			selectCard->SetRotation(rot);
			if (timer >= 0.5f) {
				//終わり。
				timer = 0.0f;
				execStep = enExecStep_PickupMultiplyCard;
			}
		}
	}break;
	case enExecStep_PickupMultiplyCard: {
		if (multiplyCard) {
			if (timer < 0.5f) {
				CVector3 pos = multiplyCard->GetPosition();
				pos.z -= 2.0f;
				if (playerNo == 1) {
					pos.y -= 3.0f;
				}
				else {
					pos.y += 3.0f;
				}
				multiplyCard->SetPosition(pos);
			}
			else {
				timer = 0.0f;
				execStep = enExecStep_RotateMultiplyCard;
			}
		}
		else {
			timer = 0.0f;
			execStep = enExecStep_Wait;
		}
	}break;
	case enExecStep_RotateMultiplyCard: {
		if (playerNo == 0) {
			//Playerのときはいらない。
			timer = 0.0f;
			execStep = enExecStep_Wait;
		}
		else {
			float t = min(1.0f, timer / 0.5f);
			float angle = CMath::PI + (CMath::PI * 2.0f - CMath::PI) * t;
			CQuaternion rot;
			rot.SetRotation(CVector3::AxisY, angle);
			multiplyCard->SetRotation(rot);
			if (timer >= 0.5f) {
				//終わり。
				timer = 0.0f;
				execStep = enExecStep_Wait;
			}
		}
	}break;
	case enExecStep_Wait:
		if (timer > 0.5f) {
			DeleteGO(this);
			execStep = enExecStep_End;
		}
		break;
	}
}
