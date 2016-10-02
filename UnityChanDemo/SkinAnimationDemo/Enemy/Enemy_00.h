/*!
 * @brief	タイプ0の敵。
 */

#pragma once

#include "CharacterController.h"

/*!
 * @brief	タイプ0の敵。
 */
class Enemy_00 : public IGameObject{
	enum EnAnimation {
		enAnimStand,
		enAnimWalk,
		enAnimAttack,
	};
	//状態
	enum EnState {
		enState_Search,	//徘徊中。
		enState_Find,	//発見状態。
	};
public:
	Enemy_00();
	~Enemy_00();
	void Init( const char* modelPath, CVector3 pos, CQuaternion	rotation);
	void Start() override;
	void Update() override;
	void Render(CRenderContext& renderContext) override;
private:
	void PlayAnimation(EnAnimation animNo);
private:
	CSkinModelDataHandle			skinModelData;
	CSkinModel						skinModel;			//スキンモデル。
	CAnimation						animation;			//アニメーション。
	CLight							light;				//ライト。
	CVector3						position;			//位置
	CQuaternion						rotation;			//回転。
	CVector3						initPosition;		//初期位置。
	EnState							state;				//ステート。
	CVector3						moveDirection;		//進行方向。
	float							timer;				//タイマ
	CharacterController				characterController;	//キャラクタコントローラ。
	int								currentAnimNo;			//現在のアニメーション番号。
	float							moveSpeed;
};