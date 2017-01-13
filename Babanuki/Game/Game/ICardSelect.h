/*!
 * @brief	カード選択処理の基底クラス。
 */

#pragma once

class Player;
/*!
 * @brief	カード選択処理。
 */
class ICardSelect : public IGameObject{
public:
	/*!
	 * @brief	初期化。
	 *@param[in]	targetPlayer	カードを引く相手になるプレイヤー。
	 */
	void Init( Player* targetPlayer );
	bool Start() override;
	void Update() override;
	/*!
	 * @brief	カードを決定したか判定。
	 */
	bool IsDecide() const
	{
		return state == enState_Decide;
	}
	/*!
	 * @brief	選択したカードの番号を取得。
	 */
	int GetSelectCardNo() const
	{
		return selectCardNo;
	}
private:
	virtual void UpdateSelectCard() = 0;
protected:
	enum EnState{
		enState_SelectCard,
		enState_Decide,
	};
	Player*		targetPlayer = NULL;
	int			selectCardNo = 0;				//選択したカードの番号。
	CLight		selectLight;					//選択した時のライト。
	EnState		state = enState_SelectCard;		//カード選択中。
};

/*!
 * @brief	プレイヤーのカード選択処理。
 */
class CardSelectPlayer : public ICardSelect
{
private:
	void UpdateSelectCard() override;
};
/*!
 * @brief	Comのカード選択処理。
 */
class CardSelectCom : public ICardSelect
{
private:
	float timer = 0.0f;
private:
	bool Start() override;
	void UpdateSelectCard() override;
};