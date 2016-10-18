/*!
 * @brief	音源クラス。
 */

#pragma once

#include "tkEngine/Sound/tkWaveFile.h"

namespace tkEngine{
	/*!
	 * @brief	音源クラス。
	 */
	class CSoundSource : public IGameObject {
	public:
		/*!
		 * @brief	コンストラクタ。
		 */
		CSoundSource();
		/*!
		 * @brief	デストラクタ。
		 */
		~CSoundSource();
		/*!
		 * @brief	初期化。
		 *@details
		 * ワンショット再生向けの初期化。
		 *@param[in]	filePath	ファイルパス。対応しているファイルフォーマット(*.wave)
		 */
		void Init( char* filePath );
		/*!
		* @brief	初期化。
		*@details
		* ストリーミング再生向けの初期化。
		*@param[in]	filePath		ファイルパス。対応しているファイルフォーマット(*.wave)
		*@param[in] ringBufferSize	リングバッファのサイズ。
		*@param[in]	bufferSize		ストリーミングの最大バッファリングサイズ。
		*/
		void InitStreaming(char* filePath, unsigned int ringBufferSize = 3 * 1024 * 1024, unsigned int bufferingSize = 1024 * 512);
		/*!
		* @brief	開放。
		*/
		void Release();
		/*!
		* @brief	再生。
		*@param[in]	isLoop		ループ再生フラグ。
		*/
		void Play(bool isLoop);
		/*!
		* @brief	更新。
		*@param[in]	isLoop		ループ再生フラグ。
		*/
		void Update() override;
		/*!
		* @brief	ボリュームを設定。
		*@param[in]	vol		ボリューム。
		*/
		void SetVolume(float vol)
		{
			m_sourceVoice->SetVolume(vol);
		}
	private:
		void UpdateStreaming();
		void Play(char* buff, unsigned int bufferSize);
		/*!
		* @brief	ストリーミングバッファリングの開始。
		*/
		void StartStreamingBuffring();
	private:
		enum EnStreamingStatus {
			enStreamingBuffering,	//バッファリング中。
			enStreamingQueueing,	//キューイング中。
		};
		CWaveFile				m_waveFile;					//!<波形データ。
		std::unique_ptr<char[]>	m_buffer;					//!<波形データを読み込むバッファ。
		IXAudio2SourceVoice*	m_sourceVoice = nullptr;	//!<ソースボイス。
		bool					m_isLoop = false;			//!<ループフラグ。
		bool					m_isPlaying = false;		//!<再生中フラグ。
		bool					m_isStreaming = false;		//!<ストリーミング再生？
		unsigned int			m_streamingBufferSize = 0;	//!<ストリーミング用のバッファリングサイズ。
		unsigned int			m_currentBufferingSize = 0;	//!<現在のバッファリングのサイズ。
		unsigned int			m_readStartPos = 0;			//!<読み込み開始位置。
		unsigned int			m_ringBufferSize = 0;		//!<リングバッファのサイズ。
		EnStreamingStatus		m_streamingState = enStreamingBuffering;	//!<ストリーミングステータス。
	};
}
