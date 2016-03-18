/*!
 * @brief	DX9å¸ÇØÇÃÉGÉìÉWÉìèâä˙âªèàóùÅB
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/Platform/DX9/tkEngineInitializerDX9.h"


namespace tkEngine{
	void EngineInitializerDX9::Execute( const InitParam& initParam )
	{
		WNDCLASSEXW wcex;

	    wcex.cbSize = sizeof(WNDCLASSEX);

	    wcex.style          = CS_HREDRAW | CS_VREDRAW;
	    wcex.lpfnWndProc    = WndProc;
	    wcex.cbClsExtra     = 0;
	    wcex.cbWndExtra     = 0;
	    wcex.hInstance      = hInstance;
//	    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
//	    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32PROJECT1);
	    wcex.lpszClassName  = szWindowClass;
//	    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	}
}

