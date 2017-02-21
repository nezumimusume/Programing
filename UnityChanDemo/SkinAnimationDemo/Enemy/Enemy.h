/*!
 * @brief	敵の基底クラス。
 */
 
#pragma once

#include "tkEngine/character/tkCharacterController.h"
#include "AnimationEventController.h"
#include "tkEngine/culling/tkObjectFrustumCulling.h"

struct EnemyParam;
class Enemy : public IGameObject{
public:
	enum EnAnimation {
		enAnimStand,
		enAnimWalk,
		enAnimAttack,
		enAnimDamage,
		enAnimDeath,
		enNumAnim,
		enAnimInvalid = 0xffffffff
	};
	Enemy() :
		currentAnimNo(enAnimInvalid),
		moveSpeed(0.0f),
		moveDirection(CVector3::AxisZ)
	{
	}
	virtual ~Enemy()
	{
	}
	virtual void Init(const char* modelPath, CVector3 pos, CQuaternion rotation);
	bool Start() override;
	void Update() override;
	void PlayAnimation(EnAnimation animNo)
	{
		if(currentAnimNo != animNo)
		{
			animation.PlayAnimation(animNo, 0.3f);
			currentAnimNo = animNo;
		}
	}
	//同じアニメーションが再生されていても気にせずにでも最初から流す。
	void PlayAnimationForce(EnAnimation animNo)
	{
		animation.PlayAnimation(animNo, 0.3f);
		currentAnimNo = animNo;
	}
	void SetMoveSpeed(float moveSpeed)
	{
		this->moveSpeed = moveSpeed;
	}
	const CVector3& GetMoveDirection() const
	{
		return moveDirection;
	}
	void SetMoveDirection( const CVector3& dir )
	{
		moveDirection = dir;
	}
	void SetDirection(const CVector3& dir)
	{
		direction = dir;
	}
	
	

	bool IsPlayAnimation() const
	{
		return animation.IsPlay();
	}
	/*!
	* @brief	骨のワールド行列を検索
	*@details
	* 名前で検索を行っているため、遅いです。頻繁に呼ばないように。
	*@param[in]	boneName	骨の名前。
	*@return 見つかったら骨のワールド行列のアドレスを返す。見つからなかった場合はNULLを返す。
	*/
	CMatrix* FindBoneWorldMatrix(const char* boneName)
	{
		return skinModel.FindBoneWorldMatrix(boneName);
	}
	/*!
	* @brief	敵のパラメータを取得。
	*/
	const EnemyParam* GetEnemyParam() const
	{
		return enemyParam;
	}
	/*!
	* @brief	死亡したことを通知。
	*/
	void NotifyDead();
	/*!
	* @brief	座標を取得。
	*/
	const CVector3& GetPosition() const
	{
		return position;
	}
	/*!
	* @brief	ロックオン可能か判定。
	*@retval	true	ロックオン可能。
	*@retval	false	ロックオン不可能。
	*/
	virtual bool IsPossibleLockOn() const
	{
		return true;
	}
	/*!
	* @brief	高さを取得。
	*/
	float GetHeight() const
	{
		return height;
	}
	/*!
	* @brief	ローカル⊿タイムを取得。
	*/
	float GetLocalFrameDeltaTime() const
	{
		return GameTime().GetFrameDeltaTime() * deltaTimeMul;
	}
	/*!
	* @brief	⊿タイムに乗算される値を設定。
	*@param[in]	mul		グローバル⊿タイムに乗算される値。この値に0.5を設定するとエネミーの挙動が0.5倍速になります。
	*/
	void SetFrameDeltaTimeMul(float mul)
	{
		deltaTimeMul = mul;
	}
private:
	/*!
	* @brief	AABBの中心座標とハーフサイズを計算。
	*/
	void CalcAABBCenterPosAndHalfSize();
	/*!
	* @brief	スキンモデルデータの読み込みが完了した時に呼ばれるコールバック。
	*/
	virtual void OnLoadedSkinModelData() {} 
protected:

	CSkinModelDataHandle			skinModelData;
	CSkinModel						skinModel;			//スキンモデル。
	CAnimation						animation;			//アニメーション。
	CVector3						position;			//位置
	CQuaternion						rotation;			//回転。
	CVector3						centerPosition;		//中心座標。
	CVector3						aabbHalfSize;		//AABBのハーフサイズ。
	EnAnimation						currentAnimNo;		//現在のアニメーション番号。
	float							moveSpeed;			//移動速度。
	CVector3						moveDirection;		//進行方向。
	CVector3						direction;			//向き。
	int								hp;					//体力。
	const EnemyParam*				enemyParam;			//敵のパラメータ。
	CVector3						initPosition;			//初期位置。
	AnimationEventController		animationEventController;	//アニメーションイベントコントローラー。
	CCharacterController			characterController;	//キャラクタコントローラ。
	float							height;
	float							radius;
	float							timer = 0.0f;
	CObjectFrustumCulling			objectCulling;			//オブジェクトのカリング処理。
	CAabb							aabb;					//オブジェクトを内包するAABB
	char							modelFilePath[1024];
	float							deltaTimeMul = 1.0f;	//⊿タイムに乗算される値。
};