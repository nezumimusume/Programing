// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

/*!
 * @brief	íËã`Ç≈DirectX9Ç≈ìÆçÏ
 */
#define TK_PLATFORM_DX9

#if defined( TK_PLATFORM_DX9 )
#include <windows.h>
#endif // #if defined( TK_PLATFORM_DX9 )
#include <memory>
#include <d3dx9.h>
#include <d3d9.h>
#ifdef _DEBUG
#include <DxErr.h>
#pragma comment(lib, "dxerr.lib")
#endif
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include "tkEngine/typedef.h"
#include "tkEngine/math/tkMath.h"
#include "tkEngine/debug/tkAssert.h"
#include "tkEngine/debug/tkLog.h"
#include "tkEngine/policy/tkNoncopyable.h"
#include "tkEngine/math/tkMatrix.h"
#include "tkEngine/math/tkVector.h"
#include "tkEngine/graphics/tkGraphicsType.h"
#include "tkEngine/Input/tkKeyInput.h"
#include "tkEngine/tkEngine.h"
#include "tkEngine/gameObject/tkGameObjectManager.h"
#include "tkEngine/gameObject/tkGameObject.h"
#include "tkEngine/graphics/tkRenderCommand.h"
#include "tkEngine/graphics/tkRenderContext.h"

// TODO: reference additional headers your program requires here
