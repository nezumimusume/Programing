#pragma once

#include "tkEngine/graphics/tkSkinModelData.h"
#include "tkEngine/graphics/tkSkinModel.h"
#include "tkEngine/graphics/tkAnimation.h"
#include "tkEngine/graphics/tkEffect.h"
#include "tkEngine/graphics/tkCamera.h"
#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/graphics/tkTexture.h"

/*!
 * @brief	ユニティちゃん
 */
class UnityChan : public IGameObject {
	enum AnimationNo {
		AnimationStand,		//立ち。
		AnimationWalk,		//歩き。
		AnimationRun,		//走り。
		AnimationJump,		//ジャンプ。
	};
	CSkinModelData	skinModelData;		//スキンモデルデータ。
	CSkinModel		skinModel;			//スキンモデル。
	CAnimation		animation;			//アニメーション。
	CCamera			camera;				//カメラ。
	CLight			light;				//ライト。
	int				currentAnimSetNo;		
	CTexture		normalMap;			//法線マップ。
public:
	void Start() override ;
	void Update() override ;
	void Render( CRenderContext& renderContext ) override;
};