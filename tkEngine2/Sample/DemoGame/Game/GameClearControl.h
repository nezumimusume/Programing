#pragma once
class GameClearCamera;

class GameClearControl : public IGameObject
{
public:
	GameClearControl();
	~GameClearControl();
	
	void Awake() override;
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
private:
	GameClearCamera* m_gameClearCamera = nullptr;
};

