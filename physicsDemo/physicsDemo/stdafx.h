/*!
 *@brief	プリコンパイルヘッダー
 */

#ifndef _STDAFX_H_
#define _STDAFX_H_

#include <windows.h>
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/GameObject/tkGameObject.h"
#include "btBulletDynamicsCommon.h"
#include "BulletCollision\CollisionDispatch\btGhostObject.h"

enum {
	CollisionType_DebriCreator,
	CollisionType_Player,
	CollisionType_Ground
};
using namespace tkEngine;


#endif // _STDAFX_H_