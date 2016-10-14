/*!
 *@brief	敵のパラメータテーブル。
 */

#pragma once

/*!
 *@brief	敵のパラメータ。
 */
struct EnemyParam{
	const char* name;					//名前。
	const char* bloodEffectBoneName;	//血しぶきエフェクトを表示するボーンの名前。
	CVector3 bloodEffectOffsetPosition;	//血しぶきエフェクトを表示するオフセット座標。
};
static const EnemyParam g_enemyParamTable[] = {
	//enemy00
	{
		"enemy_00",
		"Bip001_Neck",
	},
	//enemy00
	{
		"enemy_01",
		"spine",
	},
	//デフォルト。
	{
		"default",
		""
	},
};