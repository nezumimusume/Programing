/*!
 * @brief	プレイヤー。
 */

#include "stdafx.h"
#include "Player.h"
#include "Common/Card.h"
#include "ICardSelect.h"
#include "tkEngine/Sound/tkSoundSource.h"

Player::Player()
{
}
Player::~Player()
{
}
bool Player::Start()
{
	//重複しているカードを除去。
	EraseMultipyCardFromList();
	//配られたカードをすべてアクティブにする。
	for (auto card : cardList)
	{
		card->SetActiveFlag(true);
	}
	UpdateCardPosition();
	return true;
}
void Player::UpdateCardPosition()
{
	const CVector2& cardSize = Card::GetSize();
	//カードを全部含んだ幅。
	float cardAllHalfWidth = ((cardSize.x * 0.5f) * cardList.size())*0.5f;
	CVector3 pos = CVector3::Zero;
	pos.x = -cardAllHalfWidth;
	if (playerNo == 0) {
		pos.y = -300.0f;
	}
	else {
		pos.y = 300.0f;
	}
	CQuaternion rot;
	rot.SetRotation(CVector3::AxisY, CMath::PI);
	for (int i = 0; i < cardList.size(); i++) {
		pos.x = -cardAllHalfWidth + (cardSize.x * 0.5f) * i;
		pos.z = -0.1f * i;
		cardList[i]->SetPosition(pos);
		
		if (playerNo == 1) {
			cardList[i]->SetRotation(rot);
		}
		else {
			cardList[i]->SetRotation(CQuaternion::Identity);
		}
	}
}
/*!
* @brief	ステータス切り替え。
*/
void Player::ChangeState(Player:: EnState state)
{
	this->state = state;
	if (state == enStateSelectCard) {
		if (playerNo == 0) {
			selectCard = NewGO<CardSelectPlayer>(0);
		}
		else {
			selectCard = NewGO<CardSelectCom>(0);
		}
		selectCard->Init(targetPlayer);
	}
}
/*!
* @brief	重複カードをリストから除去。
*/
void Player::EraseMultipyCardFromList()
{
	//番号が重複しているカードを除外していく。
	std::unique_ptr<bool[]> removeFlags;
	removeFlags.reset(new bool[cardList.size()]);
	memset(removeFlags.get(), 0, sizeof(bool) * cardList.size());
	std::vector<Card*> newCardList;
	newCardList.reserve(cardList.size());
	for (int i = 0; i < cardList.size(); i++) {
		if (removeFlags[i]) {
			//削除のフラグがすでに立っているので調べる必要なし。
			continue;
		}
		for (int j = i + 1; j < cardList.size(); j++) {
			if (removeFlags[j]) {
				//削除フラグが既に立っているので調べる必要なし。
				continue;
			}
			if (cardList[i]->GetNo() == cardList[j]->GetNo()) {
				//削除。
				removeFlags[i] = true;
				removeFlags[j] = true;
				//非アクティブに。
				cardList[i]->SetActiveFlag(false);
				cardList[j]->SetActiveFlag(false);
				break;
			}
		}
		if (!removeFlags[i]) {
			//生き残り。
			newCardList.push_back(cardList[i]);
		}
	}
	//重複なしのカードリストをコピー。
	cardList = std::move(newCardList);
}
void Player::Update()
{
	
	switch (state) {
	case enStateIdle:
		break;
	case enStateSelectCard:
		if (selectCard->IsDecide()) {
			//HandsOn-4 カード決定音の再生
			CSoundSource* se = NewGO<CSoundSource>(0);
			se->Init("Assets/sound/enter.wav");
			se->Play(false);
			//決定。
			AddGO(0, &cardSelectPerfomance);
			int selectCardNo = selectCard->GetSelectCardNo();
			std::vector<Card*>& targetCardList = targetPlayer->GetCardList();
			Card* multiplyCard = NULL;
			for (Card* card : cardList) {
				if (card->GetNo() == targetCardList[selectCardNo]->GetNo()) {
					//重複カードが見つかった。
					multiplyCard = card;
					break;
				}
			}
			cardSelectPerfomance.Init(playerNo, targetCardList[selectCardNo], multiplyCard);
			state = enStateSelectPerformance;
		}
		break;
	case enStateSelectPerformance:
		if (cardSelectPerfomance.IsEnd()) {
			int selectCardNo = selectCard->GetSelectCardNo();
			//まず選択したカードをプレイヤーの手札に挿入する。
			std::vector<Card*>& targetCardList = targetPlayer->GetCardList();
			Card* card = targetCardList[selectCardNo];
			cardList.push_back(card);
			//相手のカードリストからは除去。
			targetCardList.erase(std::find(targetCardList.begin(), targetCardList.end(), card));
			//重複カードを除去。
			EraseMultipyCardFromList();
			UpdateCardPosition();
			state = enStateIdle;
		}
		break;
	}
}