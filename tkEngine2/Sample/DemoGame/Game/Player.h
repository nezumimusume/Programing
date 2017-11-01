/*!
 * @brief	�v���C���[
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
	CSkinModel 		m_skinModel;		//!<�X�L�����f���B
	CSkinModelData	m_skinModelData;	//!<�X�L�����f���f�[�^�B
	CVector3 m_position = CVector3::Zero;			//���W�B
	CQuaternion m_rotation = CQuaternion::Identity;	//��]�B
	CAnimationClip m_animClip[enAnimationClip_num];
	CAnimation m_animation;
	prefab::CDirectionLight* m_charaLight = nullptr;	//!<�L�����N�^�p�̃��C�g�B
	CCharacterController m_charaCon;		//�L�����N�^�R���g���[���B
	CVector3 m_moveSpeed = CVector3::Zero;
	CShaderResourceView m_normalMap;		//�@���}�b�v�B
	CShaderResourceView m_specMap;			//�X�y�L�����}�b�v�B
	EnState m_state = enState_Idle;
};