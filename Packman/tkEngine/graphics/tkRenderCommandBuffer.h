/*!
 *@brief	レンダリングコマンドバッファクラス。
 */

#ifndef _TKRENDERCOMMANDBUFFER_H_
#define _TKRENDERCOMMANDBUFFER_H_

namespace tkEngine{
	/*!
	 *@brief	描画コマンドバッファ
	 */
	class CRenderCommandBuffer{
	public:
		/*!
		 *@brief	コンストラクタ
		 */
		CRenderCommandBuffer();
		/*!
		 *@brief	デストラクタ。
		 */
		~CRenderCommandBuffer();
		/*!
		 *@brief	初期化。
		 *@param[in]	size	コマンドバッファのサイズ。
		 */
		void Init(u32 size);
		/*!
		 *@brief	128バイトのコマンドを書き込み。
		 *@details	コマンドは必ず128b
		 *@param[in]	command		コマンド。
		 */
		template<class T>
		void WriteCommand128(T& command)
		{
			static_assert( sizeof(T) == 128, "command size error");
			TK_ASSERT( m_writePos + 128 <= m_size, "command buffer size over!!!");
			struct Write128Byte{
				u32 data[4]
			};
			Write128Byte* dst = reinterpret_cast<Write128Byte*>(&m_buffer[m_writePos]);
			Write128Byte* src = reinterpret_cast<Write128Byte*>(p);
			*dst = command;
			m_command.push_back(dst);
			m_writePos += 128;
		}
		/*!
		 *@brief	コマンドバッファをサブミット。
		 */
		void Submit(LPDIRECT3DDEVICE9 pD3DDevice);
	private:
		std::unique_ptr<u8[]>	m_buffer;	//!<コマンドバッファ
		std::vector<void*>		m_command;	//!<コマンド。
		u32						m_writePos;	//!<書き込み位置
		u32						m_size;		//!<コマンドバッファのサイズ。
	};
}
#endif // _TKRENDERCOMMANDBUFFER_H_