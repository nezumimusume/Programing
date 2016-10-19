/*!
 * @brief	音源クラス。
 */

#pragma once

#include "tkEngine/Sound/tkWaveFile.h"

namespace tkEngine{
	/*!
	 * @brief	音源クラス。
	 *@details
	 * このクラスには波形データをオンメモリに乗せて再生する方法と、ストリーミング再生する方法があります。</br>
	 * オンメモリに乗せる場合はCSoundSource::Initを使って初期化を行ってください。</br>
	 * ストリーミング再生を行う場合はCSoundSource::InitStreamingを使用してください。</br>
	 * オンメモリでの再生は波形データを全てメインメモリ上に乗せて再生を行う方法です。</br>
	 * ストリーミング再生はメディア(DVD、HDDなどの外部補助記憶装置)から少しづつ読み込みを行って、</br>
	 * 逐次実行していく方法です。ストリーミング再生は必要な分だけ読み込みを行い(バッファリング)を行い、</br>
	 * 再生が完了するとそのバッファを破棄します。このため、少ないメモリで大きな波形データを再生することが可能です。</br>
	 * オンメモリ再生は読み込みのオーバーヘッドが最初だけになるが、ストリーミング再生は常に読み込みのオーバーヘッドが</br>
	 * 発生するためパフォマーンスが低下します。</br>
	 * 一般的にオンメモリ再生は効果音などのようなサイズの小さなSEの再生に適しています。</br>
	 * ストリーミング再生は大きなサイズのBGMの再生に適しています。</br>
	 *@code
	 	CSoundSource soundSource;
	 	//初期化
	 	void Init()
	 	{
		 	soundSource.Init("test.wave");				//こちらで初期化するとオンメモリ再生。
		 	//soundSource.InitStreaming("test.wave");	//こちらで初期化するとストリーミング再生。
		 	soundSource.Play(true);
		}
	 	//更新処理
	 	void Update()
	 	{
	 		soundSource.Update();
		}
	 	
	 *@endcode
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
		*@details
		* リングバッファにストリーミング読み込みを行って、再生を行っていきます。</br>
		* 一度に読み込まれるデータの最大サイズはbufferingSizeです。</br>
		* 読み込まれたデータはリングバッファにコピーされていきます。</br>
		*@param[in]	filePath		ファイルパス。対応しているファイルフォーマット(*.wave)
		*@param[in] ringBufferSize	リングバッファのサイズ。(bufferSizeの倍数になっていると無駄なく活用できます。)
		*@param[in]	bufferSize		ストリーミングの最大バッファリングサイズ。
		*/
		void InitStreaming(char* filePath, unsigned int ringBufferSize = 3 * 1024 * 1024, unsigned int bufferingSize = 1024 * 512);
		/*!
		* @brief	開放。
		*@details
		* デストラクタから自動的に呼ばれます。明示的に開放を行いたい場合に使用してください。
		*/
		void Release();
		/*!
		* @brief	再生。
		*@param[in]	isLoop		ループ再生フラグ。
		*/
		void Play(bool isLoop);
		/*!
		* @brief	停止。
		*/
		void Stop()
		{
			m_sourceVoice->Stop();
		}
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
		//ストリーミング再生中の更新処理。
		void UpdateStreaming();
		//オンメモリ再生中の更新処理。
		void UpdateOnMemory();
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
		std::unique_ptr<char[]>	m_buffer;					//!<波形データを読み込むバッファ。ストリーミング再生の時はリングバッファとして利用される。
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
