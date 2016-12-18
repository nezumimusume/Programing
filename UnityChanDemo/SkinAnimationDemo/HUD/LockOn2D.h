/*!
 * @brief	ロックオン
 */
#pragma once

class Enemy;

class LockOn2D : public IGameObject{
public:
	LockOn2D();
	~LockOn2D();
	bool Start() override;
	void Update() override;
	void PostRender(CRenderContext& renderContext) override;
	
	void SetLockOnEnemy(Enemy* enemy)
	{
		m_lockOnEnemy = enemy;
	}
private:
	Enemy*  m_lockOnEnemy = NULL;		//ロックオンしている敵。
	CSprite  m_lockOnSprite;	//ロックオンスプライト。
	CTexture m_lockOnTexture;	//ロックオンテクスチャ。
};