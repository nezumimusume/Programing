/*!
 *@brief	レンダリングターゲット
 */
#ifndef _TKRENDERTARGET_H_
#define _TKRENDERTARGET_H_

#include "tkEngine/graphics/tkTexture.h"

namespace tkEngine{
	/*!
	 *@brief	レンダリングターゲット
	 */
	class CRenderTarget{
	public:
		/*!
		 *@brief	コンストラクタ
		 */
		CRenderTarget();
		/*!
		 *@brief	デストラクタ。
		 */
		~CRenderTarget();
		/*!
		 *@brief	レンダリングターゲットの作成。
		 *@param[in]	w					レンダリングターゲットの幅。
		 *@param[in]	h					レンダリングターゲットの高さ。
		 *@param[in]	mipLevel			ミップマップレベル。0を指定した場合はミップマップがサポートされているGPUでは1*1ピクセルまでのミップマップが作成される。
		 *@param[in]	colorFormat			カラーバッファのフォーマット。
		 *@param[in]	depthStencilFormat	深度ステンシルバッファのフォーマット。
		 *@param[in]	multiSampleType		マルチサンプリングの種類。
		 *@param[in]	multiSampleQuality	マルチサンプリングのクオリティ。
		 */
		void Create(
			u32 w,
			u32 h,
			u32 mipLevel,
			EFormat colorFormat,
			EFormat depthStencilFormat,
			EMultisampleType multiSampleType,
			u32 multiSampleQuality
		);
		/*!
		 *@brief	レンダリングターゲットの破棄。
		 */
		void Release();
		/*!
		*@brief	テクスチャを取得。
		*/
		CTexture* GetTexture()
		{
			return &m_texture;
		}
		LPDIRECT3DSURFACE9 GetDepthSurfaceDx()
		{
			return m_depthSurface;
		}
		LPDIRECT3DSURFACE9 GetSurfaceDx()
		{
			return m_surface;
		}
		void SetDepthSurfaceDX(LPDIRECT3DSURFACE9 depthSurface)
		{
			m_depthSurface = depthSurface;
		}
		void SetSurfaceDX(LPDIRECT3DSURFACE9 surface)
		{
			m_surface = surface;
		}
		
	private:
		LPDIRECT3DSURFACE9		m_depthSurface;		//!<深度バッファ用のサーフェイス
		LPDIRECT3DTEXTURE9		m_textureDX;		//!<書き込み先のテクスチャ。
		LPDIRECT3DSURFACE9		m_surface;			//!<サーフェイス
		CTexture				m_texture;			//!<テクスチャ。
	};
}
#endif // _TKRENDERTARGET_H_