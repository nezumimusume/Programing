/*!
 * @brief	カード。
 */

#pragma once

#include "Common/CardConst.h"

class Card : public IGameObject{
public:
	Card();
	~Card();
	/*!
	 * @brief	初期化。
	 *@param[in]	type	カードの種類。EnCardType参照。
	 *@param[in]	no		カードの番号。1～13の数字が指定されている。
	 */
	void Init(EnCardType type, int no);
	bool Start() override;
	void Update() override;
	void Render(CRenderContext& renderContext);
	/*!
	* @brief	カードのサイズを取得。
	*/
	static const CVector2& GetSize() 
	{
		static const CVector2 size(96.0f, 144.0f);
		return size;
	}
	/*!
	* @brief	座標の取得。
	*/
	const CVector3& GetPosition() const
	{
		return position;
	}
	/*!
	* @brief	座標の設定。
	*/
	void SetPosition(const CVector3& position)
	{
		this->position = position;
	}
	/*!
	* @brief	回転を設定。
	*/
	void SetRotation(const CQuaternion& rotation)
	{
		this->rotation = rotation;
	}
	/*!
	* @brief	カード番号を取得。
	*/
	int GetNo() const
	{
		return no;
	}
	/*!
	* @brief	ライトを設定。
	*/
	void SetLight(CLight& light)
	{
		model.SetLight(&light);
	}
private:
	/*!
	 * @brief	初期化ステップ。
	 */
	enum EnInitStep{
		enInitStep_StartModelLoad,	//!<モデルの読み込み開始ステップ。
		enInitStep_WaitModelLoad,	//!<モデルの読み込み待ちステップ。
	};
	CTexture* 				texture;			//!<テクスチャ。
	CSkinModelData			modelData;			//!<モデルデータ。
	CSkinModel				model;				//!<スキンモデル。
	EnCardType				type;				//!<カードの種類。
	int						no;					//!<カードナンバー。
	CVector3				position = CVector3::Zero;			//!<座標。
	CQuaternion				rotation = CQuaternion::Identity;	//!<回転。
	EnInitStep				initStep = enInitStep_StartModelLoad;
	float					angle = 0;			//!<回転角度。単位ラジアン。
};