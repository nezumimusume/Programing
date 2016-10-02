/*!
 * @brief	タイプ0の敵。
 */

#pragma once

#include "CharacterController.h"
#include "Enemy/Enemy.h"

class IEnemyState;
/*!
 * @brief	タイプ0の敵。
 */
class Enemy_00 : public Enemy{
	//状態
	enum EnLocalState {
		enLocalState_Search,	//徘徊中。
		enLocalState_Find,	//発見状態。
	};
public:
	Enemy_00();
	~Enemy_00();
	void Init( const char* modelPath, CVector3 pos, CQuaternion	rotation);
	void Start() override;
	void Update() override;
	void Render(CRenderContext& renderContext) override;
private:
	
	void InitHFSM();
private:
	std::vector<IEnemyState*>		states;				//ステートのリスト。
	CVector3						initPosition;		//初期位置。
	EnLocalState					state;				//ステート。
	CTexture						specMap;			//スペキュラマップ。
	CTexture						normalMap;			//法線マップ。
	CharacterController				characterController;	//キャラクタコントローラ。
};