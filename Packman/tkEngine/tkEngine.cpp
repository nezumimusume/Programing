/*!
 * @brief	tkEngine
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/tkEngine.h"
#include "tkEngine/gameObject/tkGameObjectManager.h"

namespace tkEngine{
	LRESULT CALLBACK CEngine::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_DESTROY:
			Instance().Final();
			PostQuitMessage(0);
			return 0;
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	bool CEngine::InitWindow(const SInitParam& initParam)
	{
		TK_ASSERT(initParam.screenHeight != 0, "screenHeight is zero");
		TK_ASSERT(initParam.screenWidth != 0, "screenWidth is zero");
		TK_ASSERT(initParam.gameObjectPrioMax != 0, "gameObjectPrioMax is zero");
		TK_ASSERT(initParam.numRenderContext != 0, "numRenderContext is zero");
		TK_ASSERT(initParam.commandBufferSizeTbl != nullptr, "commandBufferSizeTbl is null");

		m_screenHeight = initParam.screenHeight;
		m_screenWidth = initParam.screenWidth;
		WNDCLASSEX wc =
		{
			sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
			GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr,
			TEXT("D3D Tutorial"), nullptr
		};
		RegisterClassEx(&wc);
		// Create the application's window
		m_hWnd = CreateWindow(TEXT("D3D Tutorial"), TEXT("D3D Tutorial 06: Meshes"),
			WS_OVERLAPPEDWINDOW, 0, 0, m_screenWidth, m_screenHeight,
			nullptr, nullptr, wc.hInstance, nullptr);

		return m_hWnd != nullptr;
	}
	bool CEngine::InitDirectX()
	{
		if( nullptr == ( m_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) ){
			//D3Dオブジェクトを作成できなかった。
	        return false;
	    }
	    D3DPRESENT_PARAMETERS d3dpp;
	    ZeroMemory( &d3dpp, sizeof( d3dpp ) );
    	d3dpp.Windowed = TRUE;
	    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	    d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	    d3dpp.EnableAutoDepthStencil = TRUE;
    	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    	// Create the D3DDevice
	    if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
	                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
	                                      &d3dpp, &m_pD3DDevice ) ) )
	    {
	        return false;
	    }
	    return true;
	    
	}
	bool CEngine::Init(const SInitParam& initParam)
	{
		//ウィンドウ初期化。
		if (!InitWindow(initParam)) {
			return false;
		}
		//DirectX初期化。
		if (!InitDirectX()) {
			return false;
		}
		CGameObjectManager::GetInstance().Init( initParam.gameObjectPrioMax );
		//レンダリングコンテキストの初期化。
		{
			m_renderContextArray.reset(new CRenderContext[initParam.numRenderContext]);
			for (u32 i = 0; i < initParam.numRenderContext; i++) {
				m_renderContextArray[i].Init(m_pD3DDevice, initParam.commandBufferSizeTbl[i]);
			}
			m_numRenderContext = initParam.numRenderContext;
			if (m_numRenderContext > 1) {
				TK_ASSERT(initParam.renderContextMap != nullptr, "renderContextMap is nullptr!!!");
				m_renderContextMap.reset( new SRenderContextMap[m_numRenderContext]);
				memcpy(m_renderContextMap.get(), initParam.renderContextMap, sizeof(SRenderContextMap) * m_numRenderContext);
			}
		}
		ShowWindow(m_hWnd, SW_SHOWDEFAULT);
		UpdateWindow(m_hWnd);
		return true;
	}
	void CEngine::RunGameLoop()
	{
		// Enter the message loop
		MSG msg;
		ZeroMemory(&msg, sizeof(msg));
		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else {
				CGameObjectManager& goMgr = CGameObjectManager::GetInstance();
				goMgr.Execute(
					m_renderContextArray.get(), 
					m_numRenderContext, 
					m_renderContextMap.get()
				);

				m_pD3DDevice->BeginScene();
				//レンダリングコマンドのサブミット
				for( u32 i = 0; i < m_numRenderContext; i++ ){
					m_renderContextArray[i].SubmitCommandBuffer();
				}
				m_pD3DDevice->EndScene();
				m_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
			}
		}
	}
	void CEngine::Final()
	{
		m_effectManager.Release();
		if (m_pD3DDevice != nullptr)
			m_pD3DDevice->Release();

		if (m_pD3D != nullptr)
			m_pD3D->Release();
	}
}// namespace tkEngine
