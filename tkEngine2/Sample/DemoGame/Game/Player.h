/*!
 * @brief	プレイヤー
 */

#pragma once

#include "tkEngine/character/tkCharacterController.h"

class Player : public IGameObject{
public:

	bool Start() override;
	void Update() override;
	void Render(CRenderContext& rc) override;
	void OnDestroy() override;
	const CVector3& GetPosition() const
	{
		return m_position;
	}
private:
	void UpdateFSM();
	void Move();
	void Turn();
	
	
private:
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_walk,
		enAnimationClip_run,
		enAnimationClip_jump,
		enAnimationClip_damage,
		enAnimationClip_KneelDown,
		enAnimationClip_num,
	};
	enum EnState {
		enState_Idle,
		enState_Run,
		enState_Jump,
		enState_GameOver,
	};
	CSkinModel 		m_skinModel;		//!<スキンモデル。
	CSkinModelData	m_skinModelData;	//!<スキンモデルデータ。
	CVector3 m_position = CVector3::Zero;			//座標。
	CQuaternion m_rotation = CQuaternion::Identity;	//回転。
	CAnimationClip m_animClip[enAnimationClip_num];
	CAnimation m_animation;
	prefab::CDirectionLight* m_charaLight = nullptr;	//!<キャラクタ用のライト。
	CCharacterController m_charaCon;		//キャラクタコントローラ。
	CVector3 m_moveSpeed = CVector3::Zero;
	CShaderResourceView m_normalMap;		//法線マップ。
	CShaderResourceView m_specMap;			//スペキュラマップ。
	EnState m_state = enState_Idle;
};