/*!
 *@brief	レンダリングターゲット
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkRenderTarget.h"
#include "tkEngine/tkEngine.h"

namespace tkEngine{
	CRenderTarget::CRenderTarget() :
		m_depthSurface(nullptr),
		m_texture(nullptr),
		m_surface(nullptr)
	{
	}
	CRenderTarget::~CRenderTarget()
	{
		Release();
	}
	void CRenderTarget::Create( 
		u32 w, 
		u32 h, 
		u32 mipLevel,
		EFormat colorFormat,
		EFormat depthStencilFormat,
		EMultisampleType multiSampleType,
		u32 multiSampleQuality
	)
	{
		Release();
		LPDIRECT3DDEVICE9 d3dDevice = CEngine::Instance().GetD3DDevice();
		//深度バッファの作成。
		HRESULT hr = d3dDevice->CreateDepthStencilSurface(
			w,
			h,
			s_cast<D3DFORMAT>(depthStencilFormat),
			s_cast<D3DMULTISAMPLE_TYPE>(multiSampleType),
			multiSampleQuality,
			TRUE,
			&m_depthSurface,
			NULL
		);
		TK_ASSERT( SUCCEEDED(hr), "failed CreateDepthStencilSurface");
		//カラーバッファを作成。
		hr = d3dDevice->CreateTexture(
			w, 
			h,
			mipLevel,
			D3DUSAGE_RENDERTARGET,
			s_cast<D3DFORMAT>(colorFormat),
			D3DPOOL_DEFAULT,
			&m_texture,
			NULL
		);
		TK_ASSERT(SUCCEEDED(hr), "Failed CreateTexture");

		hr = m_texture->GetSurfaceLevel(0, &m_surface);
		TK_ASSERT(SUCCEEDED(hr), "Failed GetSurfaceLevel" );
	}
	void CRenderTarget::Release()
	{
		if (m_texture != nullptr) {
			m_texture->Release();
			m_texture = nullptr;
		}
		if (m_depthSurface != nullptr) {
			m_depthSurface->Release();
			m_depthSurface = nullptr;
		}
		if (m_surface != nullptr) {
			m_surface->Release();
			m_surface = nullptr;
		}
	}
}
