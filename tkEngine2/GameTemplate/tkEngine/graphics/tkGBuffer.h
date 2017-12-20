/*!
 *@brief	G-Buffer
 */

#pragma once

namespace tkEngine{
	/*!
	 *@brief	G-Buffer
	 *@details
	 * ディファード系のレンダリングエンジンで使用される、
	 * G-Bufferと同じ内容ではあるが、tkEngine2のレンダリングはForward+なので
	 * 主にポストエフェクトで使用される。
	 * このG-Bufferはモデル描画パスでMRTを利用して出力されています。
	 * また、深度テクスチャについてはZPrepassで作成されているため、このクラスは保持していない。
	 */
	class CGBuffer : Noncopyable{
	public:
		enum EnGBuffer{
			enGBufferNormal,	//!<法線。
			enGBufferNum,		//!<G-Bufferの数。
		};
		/*!
		 *@brief	コンストラクタ。
		 */
		CGBuffer();
		/*!
		 *@brief	デストラクタ。
		 */
		~CGBuffer();
		void Init();
		/*!
		 *@brief	G-Bufferを取得。
		 *@param[in]	eGBuffer	取得したいG-Bufferを指定する。
		 */
		const CRenderTarget& GetGBuffer(EnGBuffer eGBuffer) const
		{
			/*if(eGBuffer >=enGBufferNum){
				return ;
			}*/
			return m_GBuffer[eGBuffer];
		}
	private:
		
		CRenderTarget m_GBuffer[enGBufferNum];	//!<G-Buffer
	};
}