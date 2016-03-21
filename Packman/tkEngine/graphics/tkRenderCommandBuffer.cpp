/*!
 *@brief	レンダリングコマンドバッファクラス。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkRenderCommandBuffer.h"

namespace tkEngine{
	CRenderCommandBuffer::CRenderCommandBuffer() :
		m_writePos(0),
		m_size(0)
	{
	}
	CRenderCommandBuffer::~CRenderCommandBuffer()
	{
	}
	void CRenderCommandBuffer::Init(u32 size)
	{
		m_buffer.reset( new u8[size] );
		m_writePos = 0;
		m_size = size;
	}
	void CRenderCommandBuffer::Submit(LPDIRECT3DDEVICE9 pD3DDevice)
	{
		for( void* cmd : m_command ){
			CRenderCommandBase* cmdBase = reinterpret_cast<CRenderCommandBase*>(cmd);
			switch(cmdBase->GetType()){
			case eRendeCommand_Clear:
				((CRenderCommand_Clear*)(cmdBase))->Execute(pD3DDevice);
				break;
			}
		}
	}
}