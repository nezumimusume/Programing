/*!
 *@brief	シェーダーのチュートリアル00
 */
#include <d3d9.h>
#include <d3dx9effect.h>
#pragma warning( disable : 4996 ) 
#include <strsafe.h>
#pragma warning( default : 4996 )
#include <cstdlib>


LPD3DXFONT	pFont;	// フォントオブジェクト

class CStopwatch {
public:
	/*!
	*@brief	コンストラクタ。
	*/
	CStopwatch()
	{
		freq = 0;
		end = 0;
		begin = 0;
		elapsed = 0.0;
		elapsedMill = 0.0;
		elapsedMicro = 0.0;
	}
	/*!
	*@brief	デストラクタ。
	*/
	~CStopwatch()
	{
	}
	/*!
	*@brief	計測開始。
	*/
	void Start()
	{
		::QueryPerformanceCounter((LARGE_INTEGER*)&begin);
	}
	/*!
	*@brief	計測終了
	*/
	void Stop()
	{
		::QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
		::QueryPerformanceCounter((LARGE_INTEGER*)&end);
		elapsed = double(end - begin) / freq;
		elapsedMill = elapsedMicro * 1000.0;
		elapsedMicro = elapsedMill * 1000.0;
	}
	/*!
	*@brief	経過時間を取得(単位:秒)
	*/
	double GetElapsed() const
	{
		return elapsed;
	}
	/*!
	*@brief	経過時間を取得(単位:ミリ秒)
	*/
	double GetElapsedMillisecond() const
	{
		return elapsedMill;
	}
	/*!
	*@brief	経過時間を取得(単位:マイクロ秒)
	*/
	double GetElapsedMicrosecond() const
	{
		return elapsedMicro;
	}
private:
	LONGLONG freq;
	LONGLONG end;
	LONGLONG begin;
	double elapsed;			//経過時間(単位：秒)
	double elapsedMill;		//経過時間(単位：ミリ秒)
	double elapsedMicro;	//経過時間(単位：マイクロ秒)

};
//-----------------------------------------------------------------------------
// グローバル変数。
//-----------------------------------------------------------------------------
LPDIRECT3D9             g_pD3D = NULL;		
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL;
ID3DXEffect*			g_pEffect = NULL;	

D3DXMATRIX				g_viewMatrix;		//ビュー行列。カメラ行列とも言う。
D3DXMATRIX				g_projectionMatrix;	//プロジェクション行列。ビュー空間から射影空間に変換する行列。
D3DXMATRIX				g_worldMatrix;		//ワールド行列。モデルローカル空間から、ワールド空間に変換する行列。
D3DXMATRIX				g_rotationMatrix;	//回転行列。法線を回すために必要なので別途用意。

LPD3DXMESH				g_pMesh = NULL;
LPDIRECT3DTEXTURE9*	 	g_pMeshTextures = NULL; 	// Textures for our mesh
DWORD              	 	g_dwNumMaterials = 0L;   	// Number of mesh materials


static const int		LIGHT_NUM = 4;
D3DXVECTOR4 			g_diffuseLightDirection[LIGHT_NUM];	//ライトの方向。
D3DXVECTOR4				g_diffuseLightColor[LIGHT_NUM];		//ライトの色。
D3DXVECTOR4				g_ambientLight;						//環境光
//ここからインスタンシング描画で使うグローバル変数。
IDirect3DVertexBuffer9* worldMatrixBuffer = NULL;			//ワールド行列のバッファ。
IDirect3DVertexDeclaration9* vertexDecl = NULL;			//頂点定義。
static const int NUM_TIGER = 5000;
D3DXMATRIX worldMatrix[NUM_TIGER];
/*!
 *@brief	シェーダーエフェクトファイル(*.fx)をロード。
 */
void LoadEffectFile()
{
	LPD3DXBUFFER  compileErrorBuffer = NULL;
	//シェーダーをコンパイル。
	HRESULT hr = D3DXCreateEffectFromFile(
		g_pd3dDevice,
		"basic.fx",
		NULL,
		NULL,
#ifdef _DEBUG
		D3DXSHADER_DEBUG,
#else
		D3DXSHADER_SKIPVALIDATION,
#endif
		NULL,
		&g_pEffect,
		&compileErrorBuffer
		);
	if (FAILED(hr)) {
		MessageBox(NULL, (char*)(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
		std::abort();
	}
}
//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D(HWND hWnd)
{
	// Create the D3D object.
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	// Set up the structure used to create the D3DDevice
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	// Create the D3DDevice
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}

	// Device state would normally be set here
	//シェーダーエフェクトファイルのロード。
	LoadEffectFile();

	D3DXCreateFont(
		g_pd3dDevice,				// Direct3Dデバイス
		24,						// 高さ
		10,						// 幅
		FW_REGULAR,				// フォントの太さ 普通
		NULL,					// 下線
		FALSE,					// 斜体
		SHIFTJIS_CHARSET,		// 文字セット
		OUT_DEFAULT_PRECIS,		// 出力制度は普通
		PROOF_QUALITY,			// 文字品質を重視
		FIXED_PITCH | FF_SCRIPT,	// ピッチとファミリ
		TEXT("ＭＳ　Ｐゴシック"),	// フォント名
		&pFont);					// ID3DXFontポインタ


	return S_OK;
}

/*!
 *@brief	プロジェクション行列の初期化。
 */
void InitProjectionMatrix()
{
	for (int i = 0; i < NUM_TIGER; i++) {
		D3DXMatrixIdentity(&worldMatrix[i]);
		worldMatrix[i].m[3][0] = ((i % 30) - 15) * 1.0f;
		worldMatrix[i].m[3][1] = (i / 30) * 1.0f;
	}

	D3DXMatrixIdentity( &g_rotationMatrix );
	
	D3DXVECTOR3 vEyePt( 0.0f, 0.0f,-10.0f );
    D3DXVECTOR3 vLookatPt( 0.0f,0.0f, 0.0f );
    D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
    D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH( &g_viewMatrix, &vEyePt, &vLookatPt, &vUpVec );
    
    D3DXMATRIXA16 matProj;
    D3DXMatrixPerspectiveFovLH( &g_projectionMatrix, D3DX_PI / 4, 1.0f, 1.0f, 100.0f );
}


//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
	if (g_pMeshTextures != NULL) {
		for (int i = 0; i < g_dwNumMaterials; i++) {
			g_pMeshTextures[i]->Release();
		}
		delete[] g_pMeshTextures;
	}
	if (vertexDecl != NULL) {
		vertexDecl->Release();
	}
	if (worldMatrixBuffer != NULL) {
		worldMatrixBuffer->Release();
	}
	if (g_pMesh != NULL) {
		g_pMesh->Release();
	}
	if (g_pEffect != NULL) {
		g_pEffect->Release();
	}
	if (g_pd3dDevice != NULL)
		g_pd3dDevice->Release();

	if (g_pD3D != NULL)
		g_pD3D->Release();
}
/*!
 *@brief	ライトを更新。
 */
void UpdateLight()
{
	g_diffuseLightDirection[0] = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	
	//ディフューズライト。
	g_diffuseLightColor[0] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

	//環境光。
	g_ambientLight = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
}
/*!
*@brief	ワールド行列を頂点バッファにコピー。
*/
void CopyWorldMatrixToVertexBuffer()
{
	D3DVERTEXBUFFER_DESC desc;
	worldMatrixBuffer->GetDesc(&desc);
	D3DXMATRIX* pData;
	worldMatrixBuffer->Lock(0, desc.Size, (void**)&pData, D3DLOCK_DISCARD);
	
	for (int i = 0; i < NUM_TIGER; i++) {
		
		*pData = worldMatrix[i];
		pData++;
	}
	worldMatrixBuffer->Unlock();
}
//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Render()
{
	CStopwatch sw;
	sw.Start();
	// Clear the backbuffer to a blue color
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	
	static int renderCount = 0;
	static bool isInstancing = true;
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		renderCount++;
		//ワールド行列を更新。
		static int renderCount = 0;
		renderCount++;
		D3DXMATRIXA16 rot;
		D3DXMatrixRotationY(&rot, renderCount / 50.0f);
		for (int i = 0; i < NUM_TIGER; i++) {
			//回転成分をコピー。
			memcpy(worldMatrix[i].m, rot.m, sizeof(float) * 12);
		}
		//ライトを更新
		UpdateLight();
		// Turn on the zbuffer
		g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		
		//シェーダー適用開始。
		if (isInstancing) {
			g_pEffect->SetTechnique("SkinModelInstancing");
		}
		else {
			g_pEffect->SetTechnique("SkinModel");
		}
		g_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		g_pEffect->BeginPass(0);

		//定数レジスタに設定するカラー。
		D3DXVECTOR4 color( 1.0f, 0.0f, 0.0f, 1.0f);
		
		//ビュー行列の転送。
		g_pEffect->SetMatrix("g_viewMatrix", &g_viewMatrix);
		//プロジェクション行列の転送。
		g_pEffect->SetMatrix("g_projectionMatrix", &g_projectionMatrix);
		//回転行列を転送。
		g_pEffect->SetMatrix( "g_rotationMatrix", &g_rotationMatrix );
		//ライトの向きを転送。
		g_pEffect->SetVectorArray("g_diffuseLightDirection", g_diffuseLightDirection, LIGHT_NUM );
		//ライトのカラーを転送。
		g_pEffect->SetVectorArray("g_diffuseLightColor", g_diffuseLightColor, LIGHT_NUM );
		//環境光を設定。
		g_pEffect->SetVector("g_ambientLight", &g_ambientLight);

		
		
		if (isInstancing) {
			
			g_pEffect->SetTexture("g_diffuseTexture", g_pMeshTextures[0]);

			//DrawSubsetを使用するとインスタンシング描画が行えないので
			//g_pMeshから頂点バッファ、インデックスバッファを引っ張ってきて、直接描画する。
			LPDIRECT3DVERTEXBUFFER9 vb;
			LPDIRECT3DINDEXBUFFER9 ib;
			g_pMesh->GetVertexBuffer(&vb);
			g_pMesh->GetIndexBuffer(&ib);
			
			DWORD fvf = g_pMesh->GetFVF();
			DWORD stride = D3DXGetFVFVertexSize(fvf);
			
			g_pd3dDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | NUM_TIGER);
			g_pd3dDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);

			g_pd3dDevice->SetVertexDeclaration(vertexDecl);
			
			g_pd3dDevice->SetStreamSource(0, vb, 0, stride);							//頂点バッファをストリーム0番目に設定
			g_pd3dDevice->SetStreamSource(1, worldMatrixBuffer, 0, sizeof(D3DXMATRIX));	//ワールド行列用のバッファをストリーム1番目に設定。
			//ワールド行列を頂点バッファにコピー。
			CopyWorldMatrixToVertexBuffer();
			g_pd3dDevice->SetIndices(ib);
			g_pEffect->CommitChanges();						//この関数を呼び出すことで、データの転送が確定する。描画を行う前に一回だけ呼び出す。
			g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, g_pMesh->GetNumVertices(), 0, g_pMesh->GetNumFaces());
			vb->Release();
			ib->Release();
		}
		else {
			//インスタンシングじゃない。
			//ワールド行列の転送。
			for (int i = 0; i < NUM_TIGER; i++) {
				g_pEffect->SetMatrix("g_worldMatrix", &worldMatrix[i]);
				// Meshes are divided into subsets, one for each material. Render them in
				// a loop
				for (DWORD matNo = 0; matNo < g_dwNumMaterials; matNo++)
				{
					g_pEffect->SetTexture("g_diffuseTexture", g_pMeshTextures[matNo]);
					g_pEffect->CommitChanges();						//この関数を呼び出すことで、データの転送が確定する。描画を行う前に一回だけ呼び出す。
					// Draw the mesh subset
					g_pMesh->DrawSubset(matNo);
				}
			}
		}
        
		g_pEffect->EndPass();
		g_pEffect->End();
	
		// End the scene
		g_pd3dDevice->EndScene();
	}
	sw.Stop();
	char text[256];
	sprintf(text, "fps = %lf\n", 1.0f / sw.GetElapsed());
	
	RECT rc = {
		0,		// 左上のx座標
		0,		// 左上のy座標
		640,	// 右下のx座標
		24		// 右下のy座標
	};
	// 描画
	pFont->DrawText(
		NULL,							// NULL
		text,							// 描画テキスト
		-1,								// 全て表示
		&rc,							// 表示範囲
		DT_LEFT,						// 左寄せ
		D3DCOLOR_XRGB(255, 255, 255)	// 白色
		);

	// Present the backbuffer contents to the display
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		Cleanup();
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

/*!
 *@brief	Xファイルを読み込んでジオメトリを初期化。
 */
HRESULT InitGeometry()
{
    LPD3DXBUFFER pD3DXMtrlBuffer;

    // Load the mesh from the specified file
    if( FAILED( D3DXLoadMeshFromX( "Tiger.x", D3DXMESH_SYSTEMMEM,
                                   g_pd3dDevice, NULL,
                                   &pD3DXMtrlBuffer, NULL, &g_dwNumMaterials,
                                   &g_pMesh ) ) )
    {
        // If model is not in current folder, try parent folder
        if( FAILED( D3DXLoadMeshFromX( "..\\Tiger.x", D3DXMESH_SYSTEMMEM,
                                       g_pd3dDevice, NULL,
                                       &pD3DXMtrlBuffer, NULL, &g_dwNumMaterials,
                                       &g_pMesh ) ) )
        {
            MessageBox( NULL, "Could not find tiger.x", "Meshes.exe", MB_OK );
            return E_FAIL;
        }
    }
	//法線が存在するか調べる。
	if ((g_pMesh->GetFVF() & D3DFVF_NORMAL) == 0) {
		//法線がないので作成する。
		ID3DXMesh* pTempMesh = NULL;

		g_pMesh->CloneMeshFVF(g_pMesh->GetOptions(),
			g_pMesh->GetFVF() | D3DFVF_NORMAL, g_pd3dDevice, &pTempMesh);

		D3DXComputeNormals(pTempMesh, NULL);
		g_pMesh->Release();
		g_pMesh = pTempMesh;

	}
	{
		//インスタンシング描画用の初期化。
		D3DVERTEXELEMENT9 declElement[MAX_FVF_DECL_SIZE];
		g_pMesh->GetDeclaration(declElement);
		int elementIndex = 0;
		while (true) {
			if (declElement[elementIndex].Type == D3DDECLTYPE_UNUSED) {
				//終端を発見。
				//ここからインスタンシング用の頂点レイアウトを埋め込む。
				declElement[elementIndex]   = { 1,  0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 };  // WORLD 1行目
				declElement[elementIndex+1] = { 1, 16, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 };  // WORLD 2行目
				declElement[elementIndex+2] = { 1, 32, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3 };  // WORLD 3行目
				declElement[elementIndex+3] = { 1, 48, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 4 };  // WORLD 4行目
				declElement[elementIndex+4] = D3DDECL_END();
				break;
			}
			elementIndex++;
		}
		//頂点定義の作成。
		g_pd3dDevice->CreateVertexDeclaration(declElement, &vertexDecl);
		//ワールド行列用のバッファの作成。
		g_pd3dDevice->CreateVertexBuffer(sizeof(D3DXMATRIX) * NUM_TIGER, 0, 0, D3DPOOL_MANAGED, &worldMatrixBuffer, 0);
	}
    // We need to extract the material properties and texture names from the 
    // pD3DXMtrlBuffer
    D3DXMATERIAL* d3dxMaterials = ( D3DXMATERIAL* )pD3DXMtrlBuffer->GetBufferPointer();
   
    g_pMeshTextures = new LPDIRECT3DTEXTURE9[g_dwNumMaterials];
    if( g_pMeshTextures == NULL )
        return E_OUTOFMEMORY;

    for( DWORD i = 0; i < g_dwNumMaterials; i++ )
    {
        g_pMeshTextures[i] = NULL;
        if( d3dxMaterials[i].pTextureFilename != NULL &&
            lstrlenA( d3dxMaterials[i].pTextureFilename ) > 0 )
        {
            // Create the texture
            if( FAILED( D3DXCreateTextureFromFileA( g_pd3dDevice,
                                                    d3dxMaterials[i].pTextureFilename,
                                                    &g_pMeshTextures[i] ) ) )
            {
                // If texture is not in current folder, try parent folder
                const CHAR* strPrefix = "..\\";
                CHAR strTexture[MAX_PATH];
                strcpy_s( strTexture, MAX_PATH, strPrefix );
                strcat_s( strTexture, MAX_PATH, d3dxMaterials[i].pTextureFilename );
                // If texture is not in current folder, try parent folder
                if( FAILED( D3DXCreateTextureFromFileA( g_pd3dDevice,
                                                        strTexture,
                                                        &g_pMeshTextures[i] ) ) )
                {
                    MessageBox( NULL, "Could not find texture map", "Meshes.exe", MB_OK );
                }
            }
        }
    }

    // Done with the material buffer
    pD3DXMtrlBuffer->Release();

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: wWinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
	UNREFERENCED_PARAMETER(hInst);

	// Register the window class
	WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		"Shader Tutorial", NULL
	};
	RegisterClassEx(&wc);

	// Create the application's window
	HWND hWnd = CreateWindow("Shader Tutorial", "Shader Tutorial 00",
		WS_OVERLAPPEDWINDOW, 100, 100, 500, 500,
		NULL, NULL, wc.hInstance, NULL);

	// Initialize Direct3D
	if (SUCCEEDED(InitD3D(hWnd)))
	{
		// Create the vertex buffer
		if (SUCCEEDED(InitGeometry()))
		{
			ZeroMemory( g_diffuseLightDirection, sizeof(g_diffuseLightDirection) );
			ZeroMemory( g_diffuseLightColor, sizeof(g_diffuseLightColor) );
			
			InitProjectionMatrix();
			// Show the window
			ShowWindow(hWnd, SW_SHOWDEFAULT);
			UpdateWindow(hWnd);

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
				else
					Render();
			}
		}
	}

	UnregisterClass("Shader Tutorial", wc.hInstance);
	return 0;
}
