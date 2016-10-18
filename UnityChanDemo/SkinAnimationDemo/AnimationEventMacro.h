/*!
 * @brief	�A�j���[�V�����C�x���g�֌W�̃}�N���B
 */

#pragma once

/*!
 * @brief	�A�j���[�V�����C�x���g�̏I�[�B
 */
#define END_ANIMATION_EVENT()													\
	AnimationEvent(																\
		eAnimationEventType_Invalid,											\
		0.0f,																	\
		0.0f, 0.0f, 0.0f, 0.0f, 												\
		0, 0, 0, 0, 															\
		NULL, NULL, NULL, NULL, 												\
		CVector3::Zero, CVector3::Zero, CVector3::Zero, CVector3::Zero	 		\
	)

/*!
 * @brief	�G�Ƀ_���[�W��^����	�R���W���������C�x���g�B
 *@param[in]	invokeTime			�R���W�������������鎞�ԁB�Y������A�j���[�V�������Đ�����Ă���o�ߎ��Ԃł��B�P�ʂ͕b�B
 *@param[in]	life				�R���W�������������Ă��鎞�ԁB�P�ʂ͕b�B
 *@param[in]	radius				�R���W�����̔��a�B
 *@param[in]	damage				�_���[�W�ʁB
 *@param[in]	boneName			�{�[�����B
 *@param[in]	offsetLocalVector	�{�[������̃I�t�Z�b�g���W�B
 *@param[in]	groupID				�O���[�v�h�c�B
 */
#define EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(invokeTime, life, radius, damage, boneName, offsetLocalVector, groupID)		\
	AnimationEvent(																				\
		eAnimationEventType_EmitDamageToEnemyCollision,											\
		(invokeTime),																			\
		(life), (radius), 0.0f, 0.0f,															\
		damage,groupID,0,0,																		\
		boneName, NULL, NULL, NULL,																\
		offsetLocalVector, CVector3::Zero, CVector3::Zero, CVector3::Zero						\
	)
