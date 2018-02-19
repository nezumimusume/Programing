#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"

class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	CSkinModel skinModel;							//�X�L�����f���B
	CSkinModelData skinModelData;					//�X�L�����f���f�[�^�B
	CAnimationClip m_animClip[1];					//�A�j���[�V�����N���b�v�B
	CAnimation m_animation;
	CVector3 m_pos = CVector3::Zero;
};
