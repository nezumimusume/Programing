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
#include "typedef.h"
#include "tkEngine\policy\tkNoncopyable.h"

// TODO: reference additional headers your program requires here
