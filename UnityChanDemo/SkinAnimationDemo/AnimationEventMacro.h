/*!
 * @brief	アニメーションイベント関係のマクロ。
 */

#pragma once

/*!
 * @brief	アニメーションイベントの終端。
 */
#define END_ANIMATION_EVENT()													\
	AnimationEvent(																\
		eAnimationEventType_Invalid,											\
		0.0f,																	\
		0.0f, 0.0f, 0.0f, 0.0f, 												\
		0, 0, 0, 0, 															\
		NULL, NULL, NULL, NULL, 												\
		CVector3::Zero, CVector3::Zero, CVector3::Zero, CVector3::Zero,	 		\
		NULL, NULL, NULL, NULL													\
	)

/*!
 * @brief	敵にダメージを与える	コリジョン発生イベント。
 *@param[in]	invokeTime			コリジョンが発生する時間。該当するアニメーションが再生されてから経過時間です。単位は秒。
 *@param[in]	life				コリジョンが発生している時間。単位は秒。
 *@param[in]	radius				コリジョンの半径。
 *@param[in]	damage				ダメージ量。
 *@param[in]	boneName			ボーン名。
 *@param[in]	offsetLocalVector	ボーンからのオフセット座標。
 *@param[in]	groupID				グループＩＤ。
 */
#define EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(invokeTime, life, radius, damage, boneName, offsetLocalVector, groupID)		\
	AnimationEvent(																				\
		eAnimationEventType_EmitDamageToEnemyCollision,											\
		(invokeTime),																			\
		(life), (radius), 0.0f, 0.0f,															\
		damage,groupID,0,0,																		\
		boneName, NULL, NULL, NULL,																\
		offsetLocalVector, CVector3::Zero, CVector3::Zero, CVector3::Zero,						\
		NULL, NULL, NULL, NULL																	\
	)

 /*!
 * @brief	プレイヤにダメージを与える	コリジョン発生イベント。
 *@param[in]	invokeTime			コリジョンが発生する時間。該当するアニメーションが再生されてから経過時間です。単位は秒。
 *@param[in]	life				コリジョンが発生している時間。単位は秒。
 *@param[in]	radius				コリジョンの半径。
 *@param[in]	damage				ダメージ量。
 *@param[in]	boneName			ボーン名。
 *@param[in]	offsetLocalVector	ボーンからのオフセット座標。
 *@param[in]	groupID				グループＩＤ。
 */
#define EMIT_DAMAGE_TO_PLAYER_COLLISION_EVENT(invokeTime, life, radius, damage, boneName, offsetLocalVector, groupID)		\
	AnimationEvent(																				\
		eAnimationEventType_EmitDamageToPlayerCollision,										\
		(invokeTime),																			\
		(life), (radius), 0.0f, 0.0f,															\
		damage,groupID,0,0,																		\
		boneName, NULL, NULL, NULL,																\
		offsetLocalVector, CVector3::Zero, CVector3::Zero, CVector3::Zero,						\
		NULL, NULL, NULL, NULL																	\
	)

#define EMIT_DAMAGE_TO_PLAYER_CUPSULE_COLLISION_EVENT(invokeTime, life, radius, damage, boneName, offsetLocalVector, groupID)	\
	AnimationEvent(\
		eAnimationEventType_EmitDamageToPlayerCollision, \
		(invokeTime), \
		(life), (radius), 0.0f, 0.0f, \
		damage, groupID, 1, 0, \
		boneName, NULL, NULL, NULL, \
		offsetLocalVector, CVector3::Zero, CVector3::Zero, CVector3::Zero, \
		NULL, NULL, NULL, NULL																	\
	)

 /*!
 * @brief	サウンドの発生イベント
 *@param[in]	invokeTime			サウンドを発生させる時間。該当するアニメーションが再生されてから経過時間です。単位は秒。
 *@param[in]	volume				ボリューム
 *@param[in]	filePath			サウンドのファイルパス。
 */
#define EMIT_SOUND_EVENT(invokeTime, volume, filePath)											\
	AnimationEvent(																				\
		eAnimationEventType_EmitSound,															\
		(invokeTime),																			\
		(volume), 0.0f, 0.0f, 0.0f,																\
		0,0,0,0,																				\
		NULL, NULL, NULL, NULL,																	\
		CVector3::Zero, CVector3::Zero, CVector3::Zero, CVector3::Zero,							\
		filePath, NULL, NULL, NULL																\
	)

 /*!
 * @brief	3Dサウンドの発生イベント
 *@param[in]	invokeTime			サウンドを発生させる時間。該当するアニメーションが再生されてから経過時間です。単位は秒。
 *@param[in]	volume				ボリューム
 *@param[in]	filePath			サウンドのファイルパス。
 *@param[in]	goTags				ゲームオブジェクトのタグ。
 */
#define EMIT_3D_SOUND_EVENT(invokeTime, volume, filePath, goTags)								\
	AnimationEvent(																				\
		eAnimationEventType_Emit3DSound,														\
		(invokeTime),																			\
		(volume), 0.0f, 0.0f, 0.0f,																\
		goTags,0,0,0,																			\
		NULL, NULL, NULL, NULL,																	\
		CVector3::Zero, CVector3::Zero, CVector3::Zero, CVector3::Zero,							\
		filePath, NULL, NULL, NULL																\
	)

