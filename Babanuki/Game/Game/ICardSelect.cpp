/*!
 * @brief	カード選択処理の基底クラス。
 */

#include "stdafx.h"
#include "ICardSelect.h"
#include "Player.h"
#include "Common/card.h"
#include "Scene\GameScene.h"
#include "tkEngine/Sound/tkSoundSource.h"

void ICardSelect::Init( Player* targetPlayer )
{
	this->targetPlayer = targetPlayer;
}
bool ICardSelect::Start() 
{
	std::vector<Card*>& cardList = targetPlayer->GetCardList();
	selectLight.SetAmbinetLight({ 1.0f, 0.5f, 0.5f });
	cardList[selectCardNo]->SetLight(selectLight);
	return true;
}
void ICardSelect::Update()
{
	switch (state) {
	case enState_SelectCard: {
		std::vector<Card*>& cardList = targetPlayer->GetCardList();
		int oldSelectCardNo = selectCardNo;
		UpdateSelectCard();
		if (selectCardNo != oldSelectCardNo) {
			//選択中のカードが変わった。
			cardList[oldSelectCardNo]->SetLight(g_gameScene->GetLight());
			cardList[selectCardNo]->SetLight(selectLight);
		}
	}break;
	}
}

/*!
* @brief	プレイヤーのカード選択処理。
*/
void CardSelectPlayer::UpdateSelectCard()
{
	std::vector<Card*>& cardList = targetPlayer->GetCardList();
	
	if (Pad(0).IsTrigger(enButtonLeft)) {
		//HandsOn-3 カード選択SEの再生。
		CSoundSource* se = NewGO<CSoundSource>(0);
		se->Init("Assets/sound/select.wav");
		se->Play(false);
		selectCardNo = max(0, selectCardNo - 1);
	}
	else if (Pad(0).IsTrigger(enButtonRight)) {
		//HandsOn-3 カード選択SEの再生。
		CSoundSource* se = NewGO<CSoundSource>(0);
		se->Init("Assets/sound/select.wav");
		se->Play(false);
		selectCardNo = min(cardList.size() - 1, selectCardNo + 1);
	}
	
	if (Pad(0).IsTrigger(enButtonA)) {
		cardList[selectCardNo]->SetLight(g_gameScene->GetLight());
		state = enState_Decide;
	}
}

/*!
* @brief	Comのカード選択処理。
*/
bool CardSelectCom::Start()
{
	selectCardNo = g_random.GetRandInt() % targetPlayer->GetCardList().size();
	ICardSelect::Start();
	return true;
}
void CardSelectCom::UpdateSelectCard()
{
	std::vector<Card*>& cardList = targetPlayer->GetCardList();
	timer += GameTime().GetFrameDeltaTime();
	if (timer > 0.4f) {
		timer = 0.0f;
		int t = g_random.GetRandInt() % 100;
		if (t < 20) {
			//5%の確率で決定。
			cardList[selectCardNo]->SetLight(g_gameScene->GetLight());
			state = enState_Decide;
		}
		else {
			t = g_random.GetRandInt() % 2;
			if (t == 1) {
				//右に
				selectCardNo = min(cardList.size() - 1, selectCardNo + 1);
			}
			else {
				//左に
				selectCardNo = max(0, selectCardNo - 1);
			}
		}
	}
}