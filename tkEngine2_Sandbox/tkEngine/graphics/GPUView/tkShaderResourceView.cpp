/*!
 *@brief	ShaderResourceView
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/GPUView/tkShaderResourceView.h"
#include "tkEngine/graphics/GPUBuffer/tkStructuredBuffer.h"
#include "tkEngine/tkEngine.h"

namespace tkEngine{
	CShaderResourceView::CShaderResourceView()
	{
	}
	CShaderResourceView::~CShaderResourceView()
	{
		Release();
	}
	void CShaderResourceView::Release()
	{
		if(m_srv != nullptr){
			m_srv->Release();
			m_srv = nullptr;
		}
		m_isValid = false;
	}
	bool CShaderResourceView::Create(CStructuredBuffer& structuredBuffer)
	{
		Release();
		ID3D11Buffer* pBuf = structuredBuffer.GetBody();
		if(pBuf != nullptr){
			D3D11_BUFFER_DESC descBuf;
	    	ZeroMemory( &descBuf, sizeof(descBuf) );
	   		pBuf->GetDesc( &descBuf );
	   		
	   		D3D11_SHADER_RESOURCE_VIEW_DESC desc;
	    	ZeroMemory( &desc, sizeof(desc) );
	    	desc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	    	desc.BufferEx.FirstElement = 0;
	    	
	    	desc.Format = DXGI_FORMAT_UNKNOWN;
	        desc.BufferEx.NumElements = descBuf.ByteWidth / descBuf.StructureByteStride;
	        
	        HRESULT hr = GraphicsEngine().GetD3DDevice()->CreateShaderResourceView( pBuf, &desc, &m_srv);
			if (FAILED(hr)) {
				return false;
			}
	    }
		//�L���ɂȂ�����
		m_isValid = true;
		return true;
	}
	/*!
	*@brief	�e�N�X�`���p��SRV���쐬�B
	*@param[in]	texture		�e�N�X�`���B
	*/
	bool CShaderResourceView::Create(ID3D11Texture2D* texture)
	{
		Release();
		if (texture != nullptr) {
			D3D11_TEXTURE2D_DESC texDesc;
			texture->GetDesc(&texDesc);
			D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};
			ZeroMemory(&SRVDesc, sizeof(SRVDesc));
			SRVDesc.Format = texDesc.Format;
			SRVDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;
			SRVDesc.Texture2D.MipLevels = texDesc.MipLevels;

			HRESULT hr = GraphicsEngine().GetD3DDevice()->CreateShaderResourceView(texture, &SRVDesc, &m_srv);
			if (FAILED(hr)) {
				return false;
			}
		}
		//�L���ɂȂ�����B
		m_isValid = true;
		return true;
	}
}