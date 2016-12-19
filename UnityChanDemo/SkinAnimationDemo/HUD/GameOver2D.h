/*!
 * @brief	ゲームオーバー。
 */

#pragma once

class GameOver2D : public IGameObject{
public:
	GameOver2D();
	~GameOver2D();
	bool Start() override;
	void Update() override;
	void PostRender(CRenderContext& renderContext) override;
private:
	enum State {
		State_WaitFadeIn,
		State_FadeIn,
	};
	CSprite  	m_youDeadSprite;	//you dead スプライト。
	CTexture	m_youDeadTex;		//you dead テクスチャ。
	State		m_state = State_WaitFadeIn;
	float		m_timer = 0.0f;			//タイマ。
};