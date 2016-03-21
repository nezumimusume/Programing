/*!
 *@brief	レンダリングコマンド
 */

#ifndef _TKRENDERCOMMAND_H_
#define _TKRENDERCOMMAND_H_


namespace tkEngine{
	/*!
	 *@brief	レンダリングコマンドのタイプ
	 */
	enum ERenderCommand{
		eRendeCommand_Clear,	//!<クリア
		eRenderCommand_Undef
	};
	/*!
	 *@brief	レンダリングコマンドの基底クラス。
	 */
	class CRenderCommandBase{
	private:
		ERenderCommand m_commandType;
	public:
		/*!
		 *@brief	コンストラクタ
		 */
		CRenderCommandBase(ERenderCommand commandType ) :
			m_commandType(commandType)
		{
			
		}
		/*!
		 *@brief	型情報を取得
		 */
		ERenderCommand GetType() const
		{
			return m_commandType;
		}
	};
	/*!
	 *@brief	クリアのレンダリングコマンド。
	 */
	class CRenderCommand_Clear : public CRenderCommandBase {
	private:
		DWORD m_Count;
		const D3DRECT *m_pRects;
		DWORD m_Flags;
		D3DCOLOR m_Color;
		float m_Z;
		DWORD m_Stencil;
	public:
		/*!
		 *@brief	コンストラクタ。
		 *@details
		 * 引数の意味はIDirect3DDevice9::Clearと同じ。詳細はMSDNヘルプを参照してください。
		 */
		CRenderCommand_Clear( 
			DWORD Count,
			const D3DRECT *pRects,
			DWORD Flags,
			D3DCOLOR Color,
			float Z,
			DWORD Stencil

		) :
			CRenderCommandBase(eRendeCommand_Clear),
			m_Count(Count),
			m_pRects(pRects),
			m_Flags(Flags),
			m_Color(Color),
			m_Z(Z),
			m_Stencil(Stencil)
		{
		}
		void Execute( LPDIRECT3DDEVICE9 pD3DDevice )
		{
			pD3DDevice->Clear(m_Count, m_pRects, m_Flags, m_Color, m_Z, m_Stencil);
		}
	};
};
#endif // _TKRENDERCOMMAND_H_