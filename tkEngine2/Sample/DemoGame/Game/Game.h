#pragma once
class Game : public IGameObject
{
public:
	//メンバ関数。
	Game();
	~Game();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	//メンバ変数。
	enum EnAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_walk,
		enAnimationClip_run,
		enAnimationClip_jump,
		enAnimationClip_damage,
		enAnimationClip_num,
	};
	CSkinModel m_skinModel;			//スキンモデル。
	CSkinModelData m_skinModelData;	//スキンモデルデータ。
	CVector3 m_position = CVector3::Zero;			//座標。
	CQuaternion m_rotation = CQuaternion::Identity;	//回転。
	CAnimationClip m_animClip[enAnimationClip_num];
	CAnimation m_animation;
	prefab::CDirectionLight* m_directionLight = nullptr;
};

