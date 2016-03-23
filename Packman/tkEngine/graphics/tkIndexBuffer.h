/*!
 *@brief	インデックスバッファ
 */

#ifndef _TKINDEXBUFFER_H_
#define _TKINDEXBUFFER_H_

namespace tkEngine{
	enum EIndexFormat {
		eIndexFormat16 = D3DFMT_INDEX16,	//16bitインデックス。
		eIndexFormat32 = D3DFMT_INDEX32,	//32bitインデックス。
	};
	class CIndexBuffer{
	public:
		CIndexBuffer();
		~CIndexBuffer();
		/*!
		 *@brief	インデックスバッファの作成。
		 *@param[in]	size			インデックスバッファのサイズ。
		 *@param[in]	format			インデックスバッファのフォーマット。
		 *@param[in]	pSrcIndexBuffer	ソースインデックスバッファ。作成されたインデックスバッファにコピーされます。NULLを指定可能。
		 */
		void Create( u32 size, EIndexFormat format, const void* pSrcIndexBuffer );
		/*!
		 *@brief	インデックスバッファの解放。
		 */
		void Release();
	private:
		LPDIRECT3DINDEXBUFFER9	m_pIB;	//!<インデックスバッファ。
	};
}

#endif //_TKINDEXBUFFER_H_