/*!
 * @brief	カードデッキクラス。
 */

#pragma once

class Card;

class CardDeck : public IGameObject{
private:

public:
	CardDeck();
	~CardDeck();
	bool Start() override;
	void Update() override {

	}
	/*
	*@brief 未使用カードをランダムに取得。
	*@return	未使用カードが存在しなくなったらNULLを返します。
	*/
	Card* GetUnuseCardRandom();
	/*
	*@brief 初期化が終わったか判定。
	*/
	bool IsInited() const;
private:
	static const int NUM_CARD = 53;		//!<トランプの数。
	int		numUnuseCard = NUM_CARD;	//!<未使用カードの数。
	bool    useFlags[NUM_CARD];			//!<カード使用中フラグ。
	Card*	cardList[NUM_CARD];			//!<カードのリスト。
};