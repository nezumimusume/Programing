/*!
 * @brief	マジックスキル
 */

#pragma once

class Player;
class IMagicSkill{
public:
	/*!
	 * @brief	マジックスキル。
	 */
	IMagicSkill(Player* pl) :
		player(pl)
	{
	}
	/*!
	 * @brief	デストラクタ。
	 */
	virtual ~IMagicSkill()
	{
	}
	/*!
	* @brief	魔法切り替え時に一度だけ呼ばれる関数。
	*/
	virtual void OnChangeMagic()
	{

	}
	/*!
	 * @brief	魔法発動時に一度だけ呼ばれる関数。
	 */
	virtual void OnStartMagic()
	{
	}
	/*!
	 * @brief	魔法終了時に一度だけ呼ばれる関数。
	 */
	virtual void OnEndMagic()
	{
	}
	/*!
	 * @brief	更新。
	 */
	void Update();	
private:
	/*!
	* @brief	魔法使用中に呼ばれる関数
	*/
	virtual void OnUsingMagicSkill() = 0;
	/*!
	* @brief	使用されるMPを取得。
	*/
	virtual float GetUseMP() const = 0;
protected:
	Player*		player = nullptr;				//プレイヤー
	bool		isUsingMagicSkill = false;		//魔法使用中？
};