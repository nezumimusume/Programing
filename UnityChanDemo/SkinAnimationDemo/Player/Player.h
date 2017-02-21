#pragma once


#include "AnimationEventController.h"
#include "Player/FSM/PlayerStateAttack.h"
#include "Player/FSM/PlayerStateDamage.h"
#include "Player/FSM/PlayerStateDead.h"
#include "Player/FSM/PlayerStateRun.h"
#include "Player/FSM/PlayerStateStand.h"
#include "Player/MagicSkill/IMagicSkill.h"
#include "Player/MagicSkill/MagicSkillDash.h"
#include "Player/MagicSkill/MagicSkillTimeCtr.h"
#include "Player/MagicSkill/MagicSkillStealth.h"

namespace tkEngine{
	class CParticleEmitter;
}

class Enemy;
class LockOn2D;

/*!
 * @brief	プレイヤー。
 */
class Player : public IGameObject {
private:
	static const int NUM_BATTLE_SEAT = 8;		//シートの数。
	//初期化ステップ。
	enum InitStep {
		InitStep_LoadModelData,
		InitStep_WaitModelData,
	};
public:
	enum EMagicSkill{
		eMagicSkillDash,			//!<ダッシュ力強化。
		eMagicSkillSlow,			//!<周りがスローモーション。
		eMagicSkillStopTheWorld,	//!<時間停止。
		eMagicSkillStealth,			//!<透明化。
		eMagicSkillHighJump,		//!<ジャンプ力強化。
		eMagicSkillNum,				//!<マジックスキルの数。
	};
	
	enum AnimationNo {
		AnimationInvalid = -1,
		AnimationStand,		//立ち。
		AnimationWalk,		//歩き。
		AnimationRun,		//走り。
		AnimationJump,		//ジャンプ。
		AnimationAttack_Start,
		AnimationAttack_00 = AnimationAttack_Start,	//攻撃00。
		AnimationAttack_01,	//攻撃01。
		AnimationAttack_02,	//攻撃02。
		AnimationAttack_End = AnimationAttack_02,
		AnimationDamage,	//ダメージ。
		AnimationDeath,		//死亡。
		NumAnimation,		//アニメーションの数。
	};
	//戦闘で使用するシート
	struct SBattleSeat {
		bool		isUse;			//使用中フラグ。
		int			seatNo;			//シート番号。
		CVector3	localPosition;	//ローカル座標。
		CVector3	position;		//ワールド座標。
	};
	enum EnState {
		enStateRun,			//走っている。
		enStateStand,		//立ち止まっている。
		enState_Attack,		//攻撃。
		enState_Damage,		//ダメージを受けている。
		enState_Dead,		//死亡。
	};
	bool					isUpdateAnim;		//

	Player(); 
	~Player();
	bool Start() override ;
	void Update() override ;
	void Render( CRenderContext& renderContext ) override;
	void SetPosition(const CVector3& position)
	{
		this->position = position;
	}
	const CVector3& GetPosition() const
	{
		return position;
	}
	/*!
	* @brief	状態を取得。
	*/
	EnState GetState() const
	{
		return state;
	}
	/*!
	* @brief	ポイントライトの位置を取得。
	*/
	const CVector3& GetPointLightPosition() const
	{
		return pointLightPosition;
	}
	/*!
	* @brief	ポイントライトの色を取得。
	*/
	const CVector4& GetPointLightColor() const
	{
		return pointLightColor;
	}
	/*!
	* @brief	未使用のシートを検索。
	*@param[in]	pos		未使用のシートの中からこの座標に一番近いシートを返します。
	*@return		未使用のシートがない場合はNULLが返ってくる。
	*/
	SBattleSeat* FindUnuseSeat(const CVector3& pos) ;
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
	* @brief	HPの取得。
	*/
	int GetHP() const
	{
		return hp;
	}
	/*!
	* @brief	最大HPの取得。
	*/
	int GetMaxHP() const
	{
		return maxHP;
	}
	/*!
	* @brief	MPの取得。
	*/
	float GetMP() const
	{
		return mp;
	}
	/*!
	* @brief	最大MPの取得。
	*/
	float GetMaxMP() const
	{
		return maxMP;
	}
	/*!
	 * @brief	現在スロットにセットされている魔法を取得。
	 */
	EMagicSkill GetCurrentMagicSkill() const
	{
		return currentMagicSkill;
	}
	/*!
	* @brief	プレイヤーの内部⊿タイムを設定。
	*/
	void SetLocalFrameDeltaTime(float deltaTime)
	{
		localFrameDeltaTime = deltaTime;
	}
	/*!
	* @brief	プレイヤーの内部⊿タイムを取得。
	*/
	float GetLocalFrameDeltaTime() const
	{
		return localFrameDeltaTime;
	}
	/*!
	* @brief	マジックポイントを使用する。
	*/
	void UseMagicPoint(float useMp)
	{
		mp = max(0, mp - useMp);
	}
	/*!
	* @brief	ステルス迷彩フラグを設定。
	*/
	void SetStealthFlag(bool flag)
	{
		skinModel.SetStealth(flag);
	}

	void Heel()
	{
		hp = maxHP;
	}
private:
	/*!
	* @brief	血しぶきのパーティクルをエミット。
	*/
	void EmitBloodParticle();
	/*!
	* @brief	状態切り替え。
	*/
	void ChangeState(EnState nextState);
	/*!
	* @brief	ヤラレ処理。
	*/
	void Damage();
	/*!
	* @brief	ポイントライトを更新。
	*/
	void UpdatePointLight();
	/*!
	* @brief	アニメーションコントロール。
	*/
	void AnimationControl();
	/*!
	* @brief	アニメーション再生。
	*/
	void PlayAnimation(AnimationNo animNo, float interpolateTime);
	/*!
	* @brief	バトルで使用するシートを初期化。
	*/
	void InitBattleSeats();
	/*!
	* @brief	バトルで使用するシートを更新。
	*/
	void UpdateBattleSeats();

	void UpdateStateMachine();
	
	/*!
	* @brief	マジックポイントの回復。
	*/
	void RecoverMagicPoint(float recoverMp)
	{
		mp = min(maxMP, mp + recoverMp);
	}
	/*!
	* @brief	敵をロックオン。
	*@retval	true	ロックオンできた。
	*@retval	false	ロックオンできなかった。
	*/
	bool LockOnEnemy();
	/*!
	* @brief	旋回処理。
	*/
	void Turn();
	/*!
	* @brief	スロットに設定されている魔法を更新。
	*/
	void UpdateCurrentMagicSkill();
private:

	friend class PlayerStateAttack;
	friend class PlayerStateDamage;
	friend class PlayerStateDead;
	friend class PlayerStateRun;
	friend class PlayerStateStand;
	
	CSkinModelDataHandle	skinModelData;
	CSkinModel				skinModel;							//スキンモデル。
	CAnimation				animation;							//アニメーション。
	CVector3				position;							//座標。
	CQuaternion				rotation;							//回転
	CVector3				toLightPos;							//
	CVector3				pointLightPosition;					//ポイントライトの位置。
	CVector4				pointLightColor;					//ポイントライトのカラー。
	CVector3				toLampLocalPos;						//ランプのローカル座標。
	bool					isApplyDamageTrigger = false;
	EnState					state;								//状態。
	EnState					lastFrameState;						//前のフレームの状態。
	bool					isPointLightOn;						//ポイントライトのスイッチ。
	CRigidBody				rigidBody;							//剛体。
	CCharacterController	characterController;				//キャラクタコントローラ。
	SBattleSeat				battleSeats[NUM_BATTLE_SEAT];		//シート。
	AnimationNo				reqAttackAnimNo;					//再生のリクエストを出している攻撃モーション番号。
	AnimationNo				nextAttackAnimNo;					//次の攻撃モーション番号。
	AnimationEventController	animationEventController;		//アニメーションイベントコントローラ。
	std::list<CParticleEmitter*>	particleEmitterList;
	int						hp =  100;							//ヒットポイント。
	int						maxHP = 100;						//最大ヒットポイント。
	float					mp = 300.0f;						//マジックポイント。
	float					maxMP = 300.0f;						//最大マジックポイント。
	float					radius = 0.0f;
	float					height = 0.0f;
	float					magicPointRecoverTimer = 0.0f;		//マジックポイントの回復タイマー。
	bool					isLockOn = false;					//ロックオン？
	Enemy*					lockOnEnemy = NULL;					//ロックオンしているエネミー。
	IPlayerState*			currentState = NULL;				//現在のステート。
	PlayerStateAttack		attackState;						//攻撃ステート。
	PlayerStateDamage		damageState;						//ダメージステート。
	PlayerStateDead			deadState;							//死亡ステート。
	PlayerStateRun			runState;							//走りステート。
	PlayerStateStand		standState;							//待機ステート。
	LockOn2D*				lockOn2D = NULL;						//ロックオン2D
	InitStep				initStep = InitStep_LoadModelData;		//初期化ステップ。
	EMagicSkill				currentMagicSkill = eMagicSkillDash;	//現在スロットにセットされている魔法。
	IMagicSkill*			pCurrentMagicSkill = NULL;				//現在スロットにセットされている魔法。
	MagicSkillDash			magicSkillDash;							//ダッシュ魔法。
	MagicSkillTimeCtr		magicSkillSlow;							//スロウ魔法。
	MagicSkillTimeCtr		magicSkillStop;							//時間停止魔法。
	MagicSkillStealth		magicSkillStealth;						//ステルス魔法。
	float					localFrameDeltaTime = 0.0f;				//プレイヤーの内部⊿タイム(単位：秒)。
};