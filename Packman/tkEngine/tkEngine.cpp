/*!
 * @brief	tkEngine
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/tkEngine.h"

namespace tkEngine{
	LRESULT CALLBACK CEngine::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_DESTROY:
			GetInstance().Final();
			PostQuitMessage(0);
			return 0;
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	bool CEngine::InitWindow()
	{
		WNDCLASSEX wc =
		{
			sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
			GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
			TEXT("D3D Tutorial"), NULL
		};
		RegisterClassEx(&wc);
		// Create the application's window
		m_hWnd = CreateWindow(TEXT("D3D Tutorial"), TEXT("D3D Tutorial 06: Meshes"),
			WS_OVERLAPPEDWINDOW, 100, 100, 300, 300,
			NULL, NULL, wc.hInstance, NULL);

		return m_hWnd != NULL;
	}
	bool CEngine::InitDirectX()
	{
		TK_LOG("test %d\n", 3);
		TK_ASSERT( false, "エラーが発生しました。" );
		if( NULL == ( m_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) ){
			//D3Dオブジェクトを作成できなかった。
	        return false;
	    }
	    D3DPRESENT_PARAMETERS d3dpp;
	    ZeroMemory( &d3dpp, sizeof( d3dpp ) );
    	d3dpp.Windowed = TRUE;
	    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
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
		if (!InitWindow()) {
			return false;
		}
		//DirectX初期化。
		if (!InitDirectX()) {
			return false;
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
			if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else {
				//Render();
			}
		}
	}
	void CEngine::Final()
	{
		if (m_pD3DDevice != NULL)
			m_pD3DDevice->Release();

		if (m_pD3D != NULL)
			m_pD3D->Release();
	}
}// namespace tkEngine
