/*!
 * @brief	サウンドエンジン
 */

#pragma once

namespace tkEngine{
	class CWaveFile;
	/*!
	 * @brief	サウンドエンジン。
	 */
	class CSoundEngine{
	public:
		/*!
		 * @brief	コンストラクタ。
		 */
		CSoundEngine();
		/*!
		 * @brief	デストラクタ。
		 */
		~CSoundEngine();
		/*!
		 * @brief	初期化。
		 */
		void Init();
		/*!
		 * @brief	開放。
		 */
		void Release();
		/*!
		* @brief	XAudio2のソースボイスを作成。
		*/
		IXAudio2SourceVoice* CreateXAudio2SourceVoice(CWaveFile* waveFile);
	private:
		IXAudio2* m_xAudio2 = NULL;
		IXAudio2MasteringVoice* m_masteringVoice = NULL;
	};
}