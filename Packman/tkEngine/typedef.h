#ifndef TK_ENGINE_TYPEDEF_H
#define TK_ENGINE_TYPEDEF_H

/*!
 * @brief	基本型別名定義
 */

#include <climits>
#include <float.h>
typedef signed				char		s8;		//!< 符号あり8bit整数
typedef unsigned			char		u8;		//!< 符号なし8bit整数
typedef signed				short		s16;	//!< 符号あり16bit整数
typedef unsigned			short		u16;	//!< 符号なし16bit整数
typedef	signed		int					s32;	//!< 符号あり32bit整数
typedef	unsigned	int					u32;	//!< 符号無し32bit整数
typedef	signed		__int64				s64;	//!< 符号あり64bit整数
typedef	unsigned	__int64				u64;	//!< 符号無し64bit整数
typedef	const	signed		int			cs32;	//!< 符号あり32bit整数定数
typedef	const	unsigned	int			cu32;	//!< 符号無し32bit整数定数
typedef	const	signed		__int64		cs64;	//!< 符号あり64bit整数定数
typedef	const	unsigned	__int64		cu64;	//!< 符号無し64bit整数定数
typedef	volatile	signed		int		vs32;	//!< 不揮発 符号あり32bit整数
typedef	volatile	unsigned	int		vu32;	//!< 不揮発 符号無し32bit整数
typedef	volatile	signed		__int64	vs64;	//!< 不揮発 符号あり64bit整数
typedef	volatile	unsigned	__int64	vu64;	//!< 不揮発 符号無し64bit整数

// 変数の限界
static const s32 S32_MAX = INT_MAX; 				//!< 符号あり32bit整数の最大値
static const s32 S32_MIN = INT_MIN; 				//!< 符号あり32bit整数の最小値
static const u32 U32_MAX = UINT_MAX;				//!< 符号無し32bit整数の最大値
static const s64 S64_MAX = _I64_MAX;				//!< 符号あり64bit整数の最大値
static const s64 S64_MIN = _I64_MIN;				//!< 符号あり64bit整数の最小値
static const u64 U64_MAX = _UI64_MAX;				//!< 符号無し64bit整数の最大値

#endif // #ifndef TK_ENGINE_TYPEDEF_H
