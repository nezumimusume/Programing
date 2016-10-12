/*!
 * @brief	タイプ0の敵。
 */

#pragma once

#include "CharacterController.h"
#include "Enemy/Enemy.h"
#include "tkEngine/shape/tkSphereShape.h"


class IEnemyState;
/*!
 * @brief	タイプ0の敵。
 */
class Enemy_00 : public Enemy{
	//状態
	enum EnLocalState {
		enLocalState_Search,	//徘徊中。
		enLocalState_Find,		//発見状態。
		enLocalState_Damage,	//ダメージ処理。
		enLocalState_Death,		//死亡。
	};
public:
	Enemy_00();
	~Enemy_00();
	void Init( const char* modelPath, CVector3 pos, CQuaternion	rotation);
	void Start() override;
	void Update() override;
	void Render(CRenderContext& renderContext) override;
private:
	void Damage();
	void InitHFSM();
private:
	std::vector<IEnemyState*>		states;					//ステートのリスト。
	CVector3						initPosition;			//初期位置。
	EnLocalState					state;					//ステート。
	std::vector<CTexture>			specMapList;			//スペキュラマップ。
	std::vector<CTexture>			normalMapList;			//法線マップ。
	CharacterController				characterController;	//キャラクタコントローラ。
	float							height;
	float							radius;
};