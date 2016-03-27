#ifndef _TK_CRENDERCONTEXT_H_
#define _TK_CRENDERCONTEXT_H_

#include "tkEngine/graphics/tkRenderCommandBuffer.h"

namespace tkEngine{
	/*!
	* @brief	レンダリングコンテキスト。
	*/
	class CRenderContext : Noncopyable{
	public:
		CRenderContext() {}
		~CRenderContext() {}
		/*!
		 *@brief	インスタンスの取得。
		 */
		static CRenderContext* GetInstance()
		{
			static CRenderContext instance;
			return &instance;
		}
		/*!
		 *@brief	初期化。
		 *@param[in]	pD3DDevice			Direct3Dデバイス
		 *@param[in]	commandBufferSize	コマンドバッファのサイズ。
		 */
		void Init(LPDIRECT3DDEVICE9 pD3DDevice, u32 commandBufferSize);
		/*!
		 *@brief	レンダリングコマンドを追加
		 */
		template<class T>
		void SetRenderCommand( T& command )
		{
			static_assert( sizeof(T) <= 32, "command size is over 32byte" );
			m_commandBuffer.WriteCommand32( command );
		}
		/*!
		 *@brief	コマンドバッファをサブミット
		 */
		void SubmitCommandBuffer()
		{
			m_commandBuffer.Submit(m_pD3DDevice);
		}
		/*!
		*@brief	コマンドバッファからアロケート
		*/
		void* AllocFromCommandBuffer(u32 sizeInByte)
		{
			return m_commandBuffer.Alloc(sizeInByte);
		}
	private:
		LPDIRECT3DDEVICE9		m_pD3DDevice;
		CRenderCommandBuffer 	m_commandBuffer;
	};
}

#endif // _TK_CRENDERCONTEXT_H_