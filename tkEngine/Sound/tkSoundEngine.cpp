/*!
 * @brief	サウンドエンジン
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/Sound/tkSoundEngine.h"
#include "tkEngine/Sound/tkWaveFile.h"

namespace tkEngine{
	/*!
	 * @brief	コンストラクタ。
	 */
	CSoundEngine::CSoundEngine()
	{
	}
	/*!
	 * @brief	デストラクタ。
	 */
	CSoundEngine::~CSoundEngine()
	{
		Release();
	}
	/*!
	 * @brief	初期化。
	 */
	void CSoundEngine::Init()
	{
		CoInitializeEx( NULL, COINIT_MULTITHREADED );
		unsigned int flags = 0;
#ifdef _DEBUG
		flags |= XAUDIO2_DEBUG_ENGINE;
#endif
		//XAUDIO2を初期化。
		HRESULT hr;
		if (FAILED(hr = XAudio2Create(&m_xAudio2, flags)))
		{
			
			TK_ASSERT(false, "Faild XAudio2Create");
		}
		//マスターボリュームの作成。
		if (FAILED(hr = m_xAudio2->CreateMasteringVoice(&m_masteringVoice)))
		{
			m_xAudio2->Release();
			CoUninitialize();
			TK_ASSERT(false, "Faild CreateMasteringVoice");
		}
	}
	/*!
	 * @brief	開放。
	 */
	void CSoundEngine::Release()
	{
		if(m_xAudio2 != nullptr){
			m_xAudio2->Release();
			m_xAudio2 = nullptr;
		}
		if (m_masteringVoice != nullptr) {
			m_masteringVoice->DestroyVoice();
			m_masteringVoice = nullptr;
		}
		CoUninitialize();
	}
	/*!
	* @brief	XAudio2のソースボイスを作成。
	*/
	IXAudio2SourceVoice* CSoundEngine::CreateXAudio2SourceVoice(CWaveFile* waveFile)
	{
		IXAudio2SourceVoice* pSourceVoice;
		if (FAILED(m_xAudio2->CreateSourceVoice(&pSourceVoice, waveFile->GetFormat())))
		{
			TK_LOG("Failed CreateSourceVoice");
			return nullptr;
		}
		return pSourceVoice;
	}
}