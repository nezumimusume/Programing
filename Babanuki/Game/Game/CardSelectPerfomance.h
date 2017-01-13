/*!
 * @brief	カード選択演出。
 */
#pragma once

class Card;

class CardSelectPerfomance : public IGameObject{
public:
	CardSelectPerfomance();
	~CardSelectPerfomance();
	/*!
	* @brief	初期化。
	*@param[in]	playerNo		プレイヤー番号。
	*@param[in]	selectCard		選択したカード。
	*@param[in]	multiplyCard	重複カード。ない場合はNULL。
	*/
	void Init(int playerNo, Card* selectCard, Card* multiplyCard);
	bool Start() override;
	void Update() override;
	/*!
	 * @brief	カード選択演出の終了判定。
	 */
	bool IsEnd() const
	{
		return execStep == enExecStep_End;
	}
private:
	//実行ステップ
	enum EnExecStep {
		enExecStep_PickupSelectCard,	//選択したカードのピックアップ演出。
		enExecStep_RotateSelectCard,	//選択したカードの反転演出。
		enExecStep_PickupMultiplyCard,	//重複カードのピックアップ演出。
		enExecStep_RotateMultiplyCard,	//重複カードの反転演出。
		enExecStep_Wait,				//ウェイト。
		enExecStep_End,
	};
	int playerNo = 0;
	Card* selectCard = NULL;
	Card* multiplyCard = NULL;
	float timer = 0.0f;
	EnExecStep execStep = enExecStep_PickupSelectCard;
};