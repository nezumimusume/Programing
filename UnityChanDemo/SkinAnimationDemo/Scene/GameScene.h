/*!
 *@brief	�Q�[���V�[���B
 */

#pragma once

#include "tkEngine/Sound/tkSoundSource.h"

class Map;
class Ground;
class PlayerHPBar;
class PlayerMPBar;
class Sky;
class UnityChanInstance;

class GameScene : public IGameObject{
public:
	/*!
	 *@brief	�R���X�g���N�^�B
	 */
	GameScene();
	/*!
	 *@brief	�f�X�g���N�^�B
	 */
	~GameScene();
	void OnDestroy() override;
	void Start() override;
	void Update() override;
private:
	Map*				map = NULL;
	Ground*				ground = NULL;
	PlayerHPBar*		playerHPBar = NULL;
	PlayerMPBar*		playerMPBar = NULL;
	Sky* 				sky = NULL;
	UnityChanInstance*	unityChanInstance = NULL;
	CSoundSource		bgmSoundSource;
};