/*!
 * @brief	NowLoading
 */

#pragma once


class NowLoading : public IGameObject{
public:
	NowLoading();
	~NowLoading();
	bool Start() override;
	void Update() override;
	void PostRender(CRenderContext& renderContext) override;

private:
	CSprite  	m_backGround;			//背景スプライト。
	CTexture	m_backGroundTex;		//背景テクスチャ。
	CSprite		m_icon;					//アイコンスプライト。
	CTexture	m_iconTex;							//アイコンテクスチャ。
	CQuaternion	m_rotation = CQuaternion::Identity;	//アイコンの回転。
	float		m_angle = 0.0f;
};