/*!
 * @brief	ババ抜きのプレイヤー
 */

#pragma once

#include "CardSelectPerfomance.h"

class Card;
class ICardSelect;

class Player : public IGameObject{
public:
	//ステータス。
	enum EnState {
		enStateIdle,		//待機。
		enStateSelectCard,	//カード選択中。
		enStateSelectPerformance,	//カード選択演出。
	};
	Player();
	~Player();
	bool Start() override;
	void Update() override;
	/*!
	* @brief	状態を取得。
	*/
	EnState GetState() const
	{
		return state;
	}
	/*!
	 * @brief	カードを追加。
	 */
	void AddCard(Card* card)
	{
		cardList.push_back(card);
	}
	/*!
	* @brief	プレイヤー番号を設定。
	*/
	void SetPlayerNo(int no)
	{
		playerNo = no;
	}
	/*!
	* @brief	ステータス切り替え。
	*/
	void ChangeState(EnState state);
	
	/*!
	* @brief	カードを引く相手になるプレイヤーを設定。
	*/
	void SetTargetPlayer(Player* targetPlayer)
	{
		this->targetPlayer = targetPlayer;
	}
	/*!
	* @brief	カードのリストを取得。
	*/
	std::vector<Card*>& GetCardList()
	{
		return cardList;
	}
	/*!
	* @brief	カードの座標を更新。
	*/
	void UpdateCardPosition();
private:
	/*!
	* @brief	重複カードをリストから除去。
	*/
	void EraseMultipyCardFromList();
	
private:
	
	std::vector<Card*>		cardList;				//!<配られたカードのリスト。
	int						playerNo = 0;			//!<プレイヤー番号。
	EnState					state = enStateIdle;	//!<ステート。
	Player*					targetPlayer;			//!<カードを引くプレイヤー。
	ICardSelect*			selectCard = NULL;
	CardSelectPerfomance	cardSelectPerfomance;	//!<カード選択パフォーマンス。
};