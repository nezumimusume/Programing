// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#define USE_ORTHO_PROJECTION

/*!
 * @brief	定義でDirectX9で動作
 */
#define TK_PLATFORM_DX9

#define BUILD_LEVEL_DEBUG		0		//デバッグビルド
#define BUILD_LEVEL_PREVIEW		1		//プレビュービルド
#define BUILD_LEVEL_MASTER		2		//マスタービルド。

 /*!
 * @brief	ビルドレベル。
 * @details
 *  BUILD_LEVELはBUILD_LEVEL_DEBUG、BUILD_LEVEL_PREVIEW、BUILD_LEVEL_MASTER</br>
 *	の３つの値をとります。この３つの値は下記の意味を持ちます。
 *		BUILD_LEVEL_DEBUG		完全なデバッグビルド。
 *		BUILD_LEVEL_PREVIEW		コードは最適化されているが、デバッグ機能は残っている。
 *		BUILD_LEVEL_MASTER		マスタービルド。デバッグ機能は完全に削除されている。
 * デバッグコードを埋め込む時は、BUILD_LEVEL_MASTERでは無効になるように実装してください。
 */
#ifdef _DEBUG
#define BUILD_LEVEL		BUILD_LEVEL_DEBUG
#elif defined(TK_MASTER)
#define BUILD_LEVEL		BUILD_LEVEL_MASTER
#else
#define BUILD_LEVEL		BUILD_LEVEL_PREVIEW
#endif

#if defined( TK_PLATFORM_DX9 )
#include <windows.h>
#include <mmsystem.h>
#endif // #if defined( TK_PLATFORM_DX9 )
#include <memory>
#include <d3dx9.h>
#include <d3d9.h>
#include <XInput.h> // XInput API
#include <xaudio2.h>
#include <x3daudio.h>
#include <xaudio2fx.h>
#pragma comment(lib, "winmm.lib")
#ifdef _DEBUG
#include <DxErr.h>
#pragma comment(lib, "dxerr.lib")
#endif
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include "btBulletDynamicsCommon.h"
#include "BulletCollision\CollisionDispatch\btGhostObject.h"
#include "tkEngine/typedef.h"
#include "tkEngine/graphics/tkFont.h"
#include "tkEngine/math/tkMath.h"
#include "tkEngine/debug/tkAssert.h"
#include "tkEngine/debug/tkLog.h"
#include "tkEngine/policy/tkNoncopyable.h"
#include "tkEngine/math/tkMatrix.h"
#include "tkEngine/math/tkVector.h"
#include "tkEngine/graphics/tkGraphicsType.h"
#include "tkEngine/Input/tkKeyInput.h"
#include "tkEngine/Util/tkNameKey.h"
#include "tkEngine/tkEngine.h"
#include "tkEngine/gameObject/tkGameObjectManager.h"
#include "tkEngine/gameObject/tkGameObject.h"
#include "tkEngine/graphics/tkRenderCommand.h"
#include "tkEngine/graphics/tkRenderContext.h"
#include "tkEngine/graphics/tkPIXPerfTag.h"
#include "tkEngine/timer/tkGameTime.h"
#include "tkEngine/graphics/sprite/tkSprite.h"
#include "tkEngine/math/tkAabb.h"


// TODO: reference additional headers your program requires here
