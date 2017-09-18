/*!
 * @brief	プリレンダー
 */

#ifndef _TKPRERENDER_H_
#define _TKPRERENDER_H_

#include "tkEngine/graphics/tkGraphicsConfig.h"
#include "tkEngine/graphics/preRender/tkZPrepass.h"
#include "tkEngine/graphics/preRender/tkLightCulling.h"
#include "tkEngine/graphics/preRender/tkShadowMap.h"

namespace tkEngine{
	/*!
	 * @brief	プリレンダリング。
	 */
	class CPreRender : Noncopyable{
	public:
		/*!
		 * @brief	コンストラクタ。
		 */
		CPreRender();
		/*!
		 * @brief	デストラクタ。
		 */
		~CPreRender();
		/*!
		* @brief	開放
		*/
		void Release();
		/*!
		 * @brief	作成。
		 *@param[in]	config	コンフィグ。
		 */
		void Create( const SGraphicsConfig& config );
		/*!
		* @brief	描画。
		*/
		void Render(CRenderContext& rc);
		/*!
		* @brief	更新。
		*/
		void Update() {}
		/*!
		* @brief	ZPrepassの取得。
		*/
		CZPrepass& GetZPrepass()
		{
			return m_zprepass;
		}
	private:
		SGraphicsConfig	m_config;			//!<コンフィグ。
		CZPrepass		m_zprepass;			//!<ZPrepass。
		CLightCulling	m_lightCulling;		//!<ライトカリング。
		CShadowMap		m_shadowMap;		//!<シャドウマップ。
	};
}
#endif //_TKPRERENDER_H_