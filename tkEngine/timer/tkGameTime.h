/*!
 *@brief	ゲーム時間クラス。
 * シングルトン。
 */
#pragma once

#include "tkEngine/timer/tkStopwatch.h"

namespace tkEngine{
	/*!
	 *@brief	ゲーム時間。
	 */
	class CGameTime{
		CGameTime() : 
			m_frameDeltaTime(1.0f/60.0f),
			m_isReady(false)
		{
		}
		~CGameTime()
		{
		}
	public:
		static CGameTime& GetInstance()
		{
			static CGameTime t;
			return t;
		}
		/*!
		 *@brief	1フレームの経過時間を取得(単位・秒)。
		 */
		float GetFrameDeltaTime() const
		{
			return min(1.0f/10.0f, m_frameDeltaTime);
		}
		void Update()
		{
			if(m_isReady){
				m_sw.Stop();
				m_frameDeltaTime = s_cast<float>( m_sw.GetElapsed() );
			}
			m_sw.Start();
			m_isReady = true;
		}
	private:
		float		m_frameDeltaTime;		//1フレームの経過時間。
		CStopwatch	m_sw;
		bool		m_isReady;
	};
	static CGameTime& GameTime()
	{
		return CGameTime::GetInstance();
	}
}
