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
	public:
		CRenderCommand_Clear() :
			CRenderCommandBase(eRendeCommand_Clear)
		{
		}
		void Execute( LPDIRECT3DDEVICE9 pD3DDevice )
		{
		}
	};
};
#endif // _TKRENDERCOMMAND_H_