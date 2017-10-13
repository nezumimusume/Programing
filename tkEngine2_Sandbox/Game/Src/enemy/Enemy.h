/*!
 * @brief	敵。
 */

#pragma once

#include "tkEngine/character/tkCharacterController.h"

/*!
 * @brief	敵。
 */
class Enemy : public IGameObject{
public:
	Enemy();
	~Enemy();
	bool Start() override;
	void Update() override;
	void Render(CRenderContext& rc) override;
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
private:
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_Num,
	};
	CAnimationClip	m_animationClip[enAnimationClip_Num];	//!<アニメーションクリップ
	CAnimation		m_animation;				//!<アニメーション。
	CSkinModelData	m_skinModelData;		//!<スキンモデルデータ。
	CSkinModel		m_skinModel;			//!<スキンモデル。
	CVector3		m_position;				//!<座標。
	CQuaternion		m_rotation = CQuaternion::Identity;		//!<回転。
	CCharacterController m_characterController;
};