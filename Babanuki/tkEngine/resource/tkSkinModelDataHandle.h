/*!
 * @brief	スキンモデルデータのハンドルクラス。
 */
#pragma once

namespace tkEngine{
	class CSkinModel;
	typedef std::shared_ptr<CSkinModelData> CSkinModelDataPtr;
	/*!
	* @brief	CSkinModelDataのハンドルクラス。
	*@details
	* このクラスを使用すると、すでにシーンにロード済みのモデルデータがある場合にそのデータを再利用します。</br>
	* そのためCSkinModelDataクラスを使用するよりもほとんどのケースでロード時間の短縮と、メモリ使用量の最適化が行えます。
	*/
	class CSkinModelDataHandle : Noncopyable{
		std::shared_ptr<CSkinModelData> m_originalSkinModelData;	//!<オリジナルのスキンモデルデータ。
		std::unique_ptr<CSkinModelData> m_skinModelData;			//!<スキンモデルデータ。
		bool							m_isLoadEnd = false;		//!<読み込み終了フラグ。
	public:
		/*!
		* @brief	ロード。
		*@param[in]	modelPath			モデルのファイルパス。
		*@param[in]	anim				アニメーション。
		*@param[in]	isInstancing		インスタンシングモデル？
		*@param[in]	numInstance			インスタンスの数。
		*/
		void LoadModelData(
			const char* modelPath,
			CAnimation* anim,
			bool isInstancing = false,
			int numInstance = 1
		);
		/*!
		* @brief	非同期ロード。
		* @details
		*  この関数を使用した場合はIsLoadEnd関数を使用して同期を取ってください。
		*@param[in]	modelPath			モデルのファイルパス。
		*@param[in]	anim				アニメーション。
		*@param[in]	isInstancing		インスタンシングモデル？
		*@param[in]	numInstance			インスタンスの数。
		*/
		void LoadModelDataAsync(
			const char* modelPath,
			CAnimation* anim,
			bool isInstancing = false,
			int numInstance = 1
		);
		/*!
		* @brief	読み込み終了判定。
		*/
		bool IsLoadEnd() const
		{
			return m_isLoadEnd;
		}
		/*!
		 * @brief	CSkinModelDataの生ポインタを取得。
		 */
		CSkinModelData* GetBody()
		{
			if(m_skinModelData){
				return m_skinModelData.get();
			}
			return m_originalSkinModelData.get();
		}
		/*!
		 * @brief	初期化。
		 *@details
		 * CSkinModelDataResourcesから呼ばれます。ユーザーは使用しないように。
		 */
		void Init(const std::shared_ptr<CSkinModelData>& skinModelData, CAnimation* anim, bool isClone);
		void NotifyLoadEnd()
		{
			m_isLoadEnd = true;
		}
	};
}
