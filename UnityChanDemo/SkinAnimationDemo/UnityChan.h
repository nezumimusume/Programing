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
	static CSkinModelData*	orgSkinModelData;		//スキンモデルデータ。
	CSkinModelData			skinModelData;
	CSkinModel				skinModel;			//スキンモデル。
	CAnimation				animation;			//アニメーション。
	CCamera					camera;				//カメラ。
	CLight					light;				//ライト。
	int						currentAnimSetNo;		
	CTexture				normalMap;			//法線マップ。
	CVector3				position;			//座標。
public:
	bool					isUpdateAnim;		//

	UnityChan() :
		position(CVector3::Zero),
		isUpdateAnim(false)
	{

	}
	void Start() override ;
	void Update() override ;
	void Render( CRenderContext& renderContext ) override;
	void SetPosition(const CVector3& position)
	{
		this->position = position;
	}
};