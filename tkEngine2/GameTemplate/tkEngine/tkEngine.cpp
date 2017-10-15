/*!
 *@brief	�G���W��
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/tkEngine.h"
#include "tkEngine/gameObject/tkGameObjectManager.h"
#include "tkEngine/timer/tkStopwatch.h"

namespace tkEngine {
	CEngine::CEngine()
	{

	}
	CEngine::~CEngine()
	{
		Final();
	}
	bool CEngine::Init( const SInitParam& initParam )
	{
		//�J�����g�f�B���N�g����Resource�ɁB
		SetCurrentDirectory("Resource");
		//�E�B���h�E�������B
		if(!InitWindow(initParam)){
			return false;
		}
		//GameObjectManager�̏������B
		GameObjectManager().Init(initParam.gameObjectPrioMax);
		//GraphicsEngine�̏������B
		if(!m_graphicsEngine.Init(m_hWnd, initParam)){
			return false;
		}
		//SoundEngine�̏�����
		m_soundEngine.Init();
		//�����G���W���̏������B
		m_physicsWorld.Init();

		return true;
	}
	bool CEngine::InitWindow( const SInitParam& initParam )
	{
		TK_ASSERT(initParam.screenHeight != 0, "screenHeight is zero");
		TK_ASSERT(initParam.screenWidth != 0, "screenWidth is zero");
		
		m_screenHeight = initParam.screenHeight;
		m_screenWidth = initParam.screenWidth;
		WNDCLASSEX wc =
		{
			sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
			GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr,
			TEXT("GameDemo"), nullptr
		};
		RegisterClassEx(&wc);
		// Create the application's window
		m_hWnd = CreateWindow(TEXT("GameDemo"), TEXT("GameDemo"),
			WS_OVERLAPPEDWINDOW, 0, 0, m_screenWidth, m_screenHeight,
			nullptr, nullptr, wc.hInstance, nullptr);

		ShowWindow(m_hWnd, initParam.nCmdShow);
		return m_hWnd != nullptr;
	}
	
	
	void CEngine::Final()
	{
		m_physicsWorld.Release();
		m_soundEngine.Release();
		m_graphicsEngine.Release();
		
	}
	void CEngine::RunGameLoop()
	{
		MSG msg = {0};
	    while( WM_QUIT != msg.message )
	    {
	        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
	        {
	            TranslateMessage( &msg );
	            DispatchMessage( &msg );
	        }
	        else
	        {
				//�X�V�B
				Update();
	        }
	    }
	}
	void CEngine::Update()
	{
		m_sw.Start();
		//�p�b�h�̍X�V�B
		for (auto& pad : m_pad) {
			pad.Update();
		}
		//�T�E���h�G���W���̍X�V�B
		m_soundEngine.Update();
		//GameObjectManager�X�V
		GameObjectManager().Execute();
		//�����G���W���̍X�V�B
		m_physicsWorld.Update();
		m_graphicsEngine.EndRender();
		
		m_sw.Stop();

		if (m_sw.GetElapsed() < 1.0f / 30.0f) {
			//30fps�ɊԂɍ����Ă���Ȃ疰��B
			DWORD sleepTime = static_cast<DWORD>(max(0.0, (1.0 / 30.0)*1000.0 - (DWORD)m_sw.GetElapsedMillisecond()));
			Sleep(sleepTime);
			GameTime().SetFrameDeltaTime(1.0f / 30.0f);
		}
		else {
			//�Ԃɍ����Ă��Ȃ��B
			GameTime().SetFrameDeltaTime((float)m_sw.GetElapsed());
		}
	}
	LRESULT CALLBACK CEngine::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		PAINTSTRUCT ps;
		HDC hdc;

		switch (msg)
		{
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}

		return 0;
	}
}