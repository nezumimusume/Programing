#pragma once

#include "tkEngine/character/tkCharacterController.h"

class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start() override;
	void Update() override;
	void Render(CRenderContext& rc) override;
	const CVector3& GetPosition() const
	{
		return m_position;
	}
private:
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_run,
		enAnimationClip_walk,
		enAnimationClip_Num,
	};
	CSkinModelData	m_skinModelData;		//!<スキンモデルデータ。
	CSkinModel		m_skinModel;			//!<スキンモデル。
	CAnimationClip	m_animationClip[enAnimationClip_Num];	//!<アニメーションクリップ
	CAnimation		m_animation;				//!<アニメーション。
	CVector3		m_position = CVector3::Zero;
	CVector3		m_moveSpeed = CVector3::Zero;
	CQuaternion		m_rotation = CQuaternion::Identity;
	CShaderResourceView	m_normalMapSRV;			//!<法線マップのSRV。
	CShaderResourceView m_specularMapSRV;		//!<スペキュラマップのSRV。
	CShaderResourceView	m_wnormalMapSRV;		//!<武器の法線マップのSRV。
	CShaderResourceView m_wspecularMapSRV;		//!<武器のスペキュラマップのSRV。
	CCharacterController m_characterCtr;		//!<キャラクターコントローラー。
	prefab::CPointLight* m_pointLight;			//!<ポイントライト。
};

