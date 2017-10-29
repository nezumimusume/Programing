#pragma once

class Player;
class Background;
class GameCamera;
class Game : public IGameObject
{
public:
	//メンバ関数。
	Game();
	~Game();
	bool Start() override;
	void Update() override;
	void Render(CRenderContext& rc) override;
	void OnDestroy()override;
private:
	void InitSceneLight();
private:
	Player*	m_player = nullptr;		//!<プレイヤー
	Background* m_background = nullptr;
	prefab::CDirectionLight* m_directionLight = nullptr;
	GameCamera* m_gameCamera = nullptr;
};

