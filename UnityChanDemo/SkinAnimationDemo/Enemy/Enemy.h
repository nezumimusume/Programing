/*!
 * @brief	敵の基底クラス。
 */
 
#pragma once


class Enemy : public IGameObject{
public:
	enum EnAnimation {
		enAnimStand,
		enAnimWalk,
		enAnimAttack,
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
	void PlayAnimation(EnAnimation animNo)
	{
		if(currentAnimNo != animNo)
		{
			animation.PlayAnimation(animNo, 0.3f);
			currentAnimNo = animNo;
		}
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
	const CVector3& GetPosition() const
	{
		return position;
	}
	bool IsPlayAnimation() const
	{
		return animation.IsPlay();
	}
protected:
	CSkinModelDataHandle			skinModelData;
	CSkinModel						skinModel;			//スキンモデル。
	CAnimation						animation;			//アニメーション。
	CLight							light;				//ライト。
	CVector3						position;			//位置
	CQuaternion						rotation;			//回転。
	EnAnimation						currentAnimNo;		//現在のアニメーション番号。
	float							moveSpeed;			//移動速度。
	CVector3						moveDirection;		//進行方向。
	CVector3						direction;			//向き。
};