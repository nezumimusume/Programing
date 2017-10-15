/*!
 *@brief		���O
 */

#ifndef _TKLOG_H_
#define _TKLOG_H_


namespace tkEngine{
	/*!
	 *@brief	���O�o��
	 */
	static inline void Log( const char* format, ... )
	{
		static char log[1024*10];
		va_list va;
		va_start( va, format );
		vsprintf_s( log, format, va );
		OutputDebugString( log );
		OutputDebugString("\n");
		va_end( va );
	}

	/*!
	*@brief	�x���o��
	*/
	static inline void Warning(const char* format, ...)
	{
		static char newFormat[1024 * 10] = { "TK_WARNING : " };
		strcat_s(newFormat, format);
		Log(newFormat);
	}
}

#if BUILD_LEVEL != BUILD_LEVEL_MASTER
	#define TK_LOG( format, ... )	tkEngine::Log(format, __VA_ARGS__)
	#define TK_WARNING(format, ... ) tkEngine::Warning(format, __VA_ARGS__)
#else // _DEBUG
#define TK_LOG( format, ... )
#define TK_WARNING(format, ... )
#endif // _DEBUG
#endif // _TKLOG_H_