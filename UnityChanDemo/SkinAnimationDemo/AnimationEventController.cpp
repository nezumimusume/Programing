/*!
 * @brief	アニメーションイベントコントローラ。
 */

#include "stdafx.h"
#include "AnimationEventController.h"
#include "DamageCollisionWorld.h"
#include "tkEngine/Sound/tkSoundSource.h"

AnimationEventController::AnimationEventController() :
	animation(nullptr),
	animNoLastFrame(-1),
	skinModel(nullptr)
{
}
AnimationEventController::~AnimationEventController()
{
}
void AnimationEventController::Init(CSkinModel* skinModel, CAnimation* animation, AnimationEventGroup* eventGroupTbl, int tblSize )
{
	TK_ASSERT(animation->GetNumAnimationSet() == tblSize, "tblSize is invalid");
	this->skinModel = skinModel;
	this->animation = animation;
	eventGroupExTbl.resize(tblSize);
	for (int i = 0; i < tblSize; i++) {
		eventGroupExTbl[i].eventGroup = eventGroupTbl[i];
		memset(eventGroupExTbl[i].invokeFlags, 0, sizeof(eventGroupExTbl[i].invokeFlags));
	}
}
void AnimationEventController::InvokeAnimationEvent(const AnimationEvent& event)
{
	switch (event.eventType) {
	case eAnimationEventType_EmitDamageToEnemyCollision: {
		//敵にダメージを与えるコリジョンの発生。
		CMatrix* bone = skinModel->FindBoneWorldMatrix(event.strArg[0]);
		CVector3 pos = event.vArg[0];
		bone->Mul(pos);
		g_damageCollisionWorld->Add(event.fArg[1], pos, event.fArg[0], event.iArg[0], DamageCollisionWorld::enDamageToEnemy, event.iArg[1]);
	}break;
	case eAnimationEventType_EmitDamageToPlayerCollision: {
		//プレイヤーにダメージを与えるコリジョンの発生。
		CMatrix* bone = skinModel->FindBoneWorldMatrix(event.strArg[0]);
		CVector3 pos = event.vArg[0];
		bone->Mul(pos);
		g_damageCollisionWorld->Add(event.fArg[1], event.vArg[0], event.fArg[0], event.iArg[0], DamageCollisionWorld::enDamageToPlayer, event.iArg[1]);
	}break;
	case eAnimationEventType_EmitSound: {
		//ワンショットのサウンド発生。
		CSoundSource* s = NewGO<CSoundSource>(0);
		s->Init((char*)event.strArg[0]);
		s->Play(false);
		s->SetVolume(event.fArg[0]);
	}
	default:
		break;
	}
}
void AnimationEventController::Update()
{
	TK_ASSERT(animation != nullptr, "animation is null");
	int currentAnimNo = animation->GetPlayAnimNo();
	float animTime = animation->GetLocalAnimationTime();
	if (animNoLastFrame != -1 && animNoLastFrame != currentAnimNo) {
		//アニメーションが切り替わった。
		//前のアニメーションのイベント発生フラグを初期化する。
		memset(eventGroupExTbl[animNoLastFrame].invokeFlags, 0, sizeof(eventGroupExTbl[animNoLastFrame].invokeFlags));
	}
	else if (animTime < lastFrameAnimTime) {
		//前のフレームよりもアニメーション時間が小さくなった(ループした)
		//残っているイベントを全部発生させてから初期化。
		AnimationEventGroupEx& eventGroupEx = eventGroupExTbl[currentAnimNo];
		for (
			int i = 0;
			eventGroupEx.eventGroup.event[i].eventType != eAnimationEventType_Invalid;
			i++
			) {
			if (eventGroupEx.invokeFlags[i] == false) {
				InvokeAnimationEvent(eventGroupEx.eventGroup.event[i]);
				//発生済みの印。
				eventGroupEx.invokeFlags[i] = true;
			}
		}
		memset(eventGroupExTbl[currentAnimNo].invokeFlags, 0, sizeof(eventGroupExTbl[currentAnimNo].invokeFlags));
	}
	lastFrameAnimTime = animTime;
	AnimationEventGroupEx& eventGroupEx = eventGroupExTbl[currentAnimNo];
	for (
		int i = 0;
		eventGroupEx.eventGroup.event[i].eventType != eAnimationEventType_Invalid;
		i++
		) {
		if (eventGroupEx.invokeFlags[i] == false) {
			//まだイベントが発生していない。
			if (eventGroupEx.eventGroup.event[i].time <= animTime) {
				//イベント発生する時間が経過した。
				InvokeAnimationEvent(eventGroupEx.eventGroup.event[i]);
				//発生済みの印。
				eventGroupEx.invokeFlags[i] = true;
			}
		}
	}
	animNoLastFrame = currentAnimNo;
	
}
