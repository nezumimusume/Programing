/*!
 * @brief	プリコンパイル済みヘッダー。
 */

#ifndef _STDAFX_H_
#define _STDAFX_H_


#include <windows.h>
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkSkinModelData.h"
#include "tkEngine/graphics/tkSkinModel.h"
#include "tkEngine/graphics/tkAnimation.h"
#include "tkEngine/graphics/tkEffect.h"
#include "tkEngine/graphics/tkCamera.h"
#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/graphics/tkTexture.h"
#include "tkEngine/resource/tkSkinModelDataHandle.h"
#include "tkEngine/graphics/material/tkSkinModelMaterial.h"
#include "tkEngine/Physics/tkPhysics.h"
#include "tkEngine/graphics/tkSkinModelData.h"
#include "tkEngine/graphics/tkSkinModel.h"
#include "tkEngine/graphics/tkAnimation.h"
#include "tkEngine/graphics/tkEffect.h"
#include "tkEngine/graphics/tkCamera.h"
#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/graphics/tkTexture.h"
#include "tkEngine/Physics/tkSphereCollider.h"
#include "tkEngine/Physics/tkRigidBody.h"
#include "tkEngine/character/tkCharacterController.h"
#include "tkEngine/graphics/tkAtmosphericScatteringParam.h"

using namespace tkEngine;
#include "GameCamera.h"
#include "tkEngine/random/tkRandom.h"

class Player;
class EnemyManager;
class NowLoading;
class Fade;
extern Player* g_player;
extern CRandom g_random;
extern EnemyManager* g_enemyManager;
extern NowLoading* g_nowLoading;
extern Fade* g_fade;

#endif // _STDAFX_H_