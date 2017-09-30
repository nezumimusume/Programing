/*!
 * @brief	ブルーム
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/postEffect/tkBloom.h"

namespace tkEngine{
	/*!
	 * @brief	コンストラクタ。
	 */
	CBloom::CBloom()
	{
	}
	/*!
	 * @brief	デストラクタ。
	 */
	CBloom::~CBloom()
	{
		Release();
	}
	/*!
	 * @brief	開放
	 */
	void CBloom::Release()
	{
	}
	/*!
	 * @brief	初期化。
	 */
	void CBloom::Init( const SGraphicsConfig& config )
	{
		Release();
		
		if(!config.bloomConfig.isEnable){
			return ;
		}
		m_isEnable = config.bloomConfig.isEnable;
		int w = Engine().GetGraphicsEngine().GetFrameBufferWidth();
		int h = Engine().GetGraphicsEngine().GetFrameBufferHeight();

		//輝度抽出用のレンダリングターゲットを作成。
		DXGI_SAMPLE_DESC multiSampleDesc;
		ZeroMemory(&multiSampleDesc, sizeof(multiSampleDesc));
		multiSampleDesc.Count = 1;
		multiSampleDesc.Quality = 0;
		m_luminanceRT.Create(
			w, 
			h, 
			1, 
			1, 
			DXGI_FORMAT_R16G16B16A16_FLOAT, 
			DXGI_FORMAT_UNKNOWN,
			multiSampleDesc
		);

	}
	/*!
	 * @brief	描画
	 */
	void CBloom::Render(CRenderContext& rc, CPostEffect* postEffect)
	{
	}
}