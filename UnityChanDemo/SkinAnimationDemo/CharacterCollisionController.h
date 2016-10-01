/*!
 * @brief	キャラクタのコリジョンコントロール。
 */

#pragma once

/*!
 * @brief
 */
class CharacterCollisionController{
public:
	CharacterCollisionController();
	~CharacterCollisionController();
	
	/*!
	 * @brief	実行。
	 */
	void Execute( CVector3 nextPosition );
private:
	CVector3 			position;		//座標。
	CVector3 			moveSpeed;		//移動速度。 
	bool 				isJump;			//ジャンプ中？
	SphereCollider		collider;		//コライダ。
};