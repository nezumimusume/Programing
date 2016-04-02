/*!
 * @brief	プリレンダー
 */

#ifndef _TKPRERENDER_H_
#define _TKPRERENDER_H_

#include "tkEngine/graphics/tkGraphicsConfig.h"
#include "tkEngine/graphics/preRender/tkIDMap.h"
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
		 * @brief	作成。
		 *@param[in]	config	コンフィグ。
		 */
		void Create( const SGraphicsConfig& config );
		/*!
		 * @brief	描画。
		 */
		void Render( CRenderContext& context )
		{
			m_idMap.RenderToIDMap(context);
		}
		/*!
		* @brief	IDMapの取得。
		*/
		CIDMap& GetIDMap()
		{
			return m_idMap;
		}
	private:
		SGraphicsConfig	m_config;	//!<コンフィグ。
		CIDMap			m_idMap;	//!<IDマップ
	};
}
#endif //_TKPRERENDER_H_