#pragma once
class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();
	bool Start() override;
	void Update() override;
	void Render(CRenderContext& rc) override;
private:
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_run,
		enAnimationClip_num,
	};
	CSkinModelData m_skinModelData;		//!<スキンモデルデータ。
	CSkinModel m_skinModel;				//!<スキンモデル。
	CAnimationClip m_animClip[enAnimationClip_num];
	CAnimation m_animation;
};

