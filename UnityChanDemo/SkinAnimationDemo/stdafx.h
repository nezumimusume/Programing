/*!
 * @brief	プリコンパイル済みヘッダー。
 */

#ifndef _STDAFX_H_
#define _STDAFX_H_

//#define ENEMY_TEST

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
#include "btBulletDynamicsCommon.h"
#include "BulletCollision\CollisionDispatch\btGhostObject.h"
#include "Physics\Physics.h"
using namespace tkEngine;
#include "GameCamera.h"
#include "tkEngine/random/tkRandom.h"

extern PhysicsWorld* g_physicsWorld ;
extern UnityChan* g_unityChan;
extern CRandom g_random;
#endif // _STDAFX_H_