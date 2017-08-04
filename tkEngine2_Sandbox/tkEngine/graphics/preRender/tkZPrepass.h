/*!
 *@brief	ZPrepass
 */

#pragma once 

namespace tkEngine{
	class CCamera;
	/*!
	 *@brief	ZPrepass
	 */
	class CZPrepass{
	public:
		/*!
		 *@brief	コンストラクタ
		 */
		CZPrepass();
		/*!
		 *@brief	デストラクタ。
		 */
		~CZPrepass();
		/*!
		*@brief	初期化関数。
		*/
		void Init();
		/*!
		 *@brief	描画。
		 */
		void Render(CRenderContext& rc) ;
		
		/*!
		*@brief	スキンモデルを追加。
		*/
		void AddSkinModel(CSkinModel* skinModel)
		{
			m_skinModels.push_back(skinModel);
		}
	private:
		std::vector<CSkinModel*>	m_skinModels;			//!<スキンモデルのリスト。
		CRenderTarget				m_depthBuffer;			//!<深度バッファを書き込むためのレンダリングターゲット。
	};
}