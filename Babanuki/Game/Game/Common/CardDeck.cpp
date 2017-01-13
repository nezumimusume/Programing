/*!
 * @brief	カードデッキクラス。
 */

#include "stdafx.h"
#include "Common/CardDeck.h"
#include "Common/Card.h"

CardDeck::CardDeck()
{
	memset(useFlags, 0, sizeof(useFlags));
}
CardDeck::~CardDeck()
{
	for(auto& card : cardList){
		DeleteGO(card);
	}
}
/*
*@brief 初期化が終わったか判定。
*/
bool CardDeck::IsInited() const
{
	for (auto& card : cardList) {
		if (!card || !card->IsStart()) {
			//終わっていない。
			return false;
		}
	}
	//終わり。
	return true;
}
/*
*@brief 未使用カードをランダムに取得。
*@return	未使用カードが存在しなくなったらNULLを返します。
*/
Card* CardDeck::GetUnuseCardRandom()
{
	if (numUnuseCard == 0) {
		//もうないよ。
		return NULL;
	}
	int pickUpCardNo = g_random.GetRandInt() % numUnuseCard;
	int currentUnuseCardNo = 0;
	//未使用カードを探す。
	for (int i = 0; i < NUM_CARD; i++) {
		if (useFlags[i]) {
			//使用中。
			continue;
		}
		
		if (pickUpCardNo == currentUnuseCardNo) {
			//未使用カードを発見。
			//未使用カードを減らす。
			numUnuseCard--;
			//使用中にする。
			useFlags[i] = true;
			return cardList[i];
		}
		currentUnuseCardNo++;
	}
	return NULL;
}
bool CardDeck::Start()
{
	static EnCardType cardType[] = {
		enCardType_Heart,
		enCardType_Dia,
		enCardType_Spade,
		enCardType_Clover,
	};
	int numCard = 0;
	for( auto type : cardType ){
		for(int i = 0; i < 13; i++ ){
			//カードを生成していく。
			Card* card = NewGO<Card>(0);
			card->Init(type, i+1);
			cardList[numCard] = card;
			numCard++;
		}
	}
	//最後にジョーカーを生成。
	Card* card = NewGO<Card>(0);
	card->Init(enCardType_Joker, -1);
	cardList[numCard] = card;
	return true;
}