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
		void Init(int size);
		/*!
		 *@brief	32バイトのコマンドを書き込み。
		 *@details	コマンドは必ず32byte
		 *@param[in]	command		コマンド。
		 */
		template<class T>
		void WriteCommand32(T& command)
		{
			static_assert( sizeof(T) <= 32, "command size error\n");
			TK_ASSERT( m_writePos + 32 <= m_size, "command buffer size over!!!");
			struct Write32Byte{
				int data[8];
			};
			Write32Byte* dst = reinterpret_cast<Write32Byte*>(&m_buffer[m_writePos]);
			Write32Byte* src = reinterpret_cast<Write32Byte*>(&command);
			*dst = *src;
			m_command.push_back(dst);
			m_writePos += 32;
		}
		/*!
		*@brief	コマンドバッファからアロケート
		*/
		void* Alloc(int sizeInByte)
		{
			TK_ASSERT(m_writePos + sizeInByte <= m_size, "command buffer size over!!!");
			void* p = &m_buffer[m_writePos];
			m_writePos += sizeInByte;
			return p;
		}
		/*!
		 *@brief	コマンドバッファをサブミット。
		 */
		void Submit(LPDIRECT3DDEVICE9 pD3DDevice);
	private:
		std::unique_ptr<unsigned char[]>	m_buffer;	//!<コマンドバッファ
		std::vector<void*>		m_command;	//!<コマンド。
		int						m_writePos;	//!<書き込み位置
		int						m_size;		//!<コマンドバッファのサイズ。
	};
}
#endif // _TKRENDERCOMMANDBUFFER_H_