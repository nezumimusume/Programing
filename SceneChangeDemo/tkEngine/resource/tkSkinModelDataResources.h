/*!
 * @brief	CSkinModelDataのリソース管理。
 */
#pragma once

#include <mutex>
#include <queue>
#include "tkEngine/thread/tkCriticalSection.h"

namespace tkEngine{
	class CSkinModelDataHandle;
	class CSkinModel;
	typedef std::shared_ptr<CSkinModelData> CSkinModelDataPtr;
	/*!
	 * @brief	CSkinModelDataのリソース管理。
	 */
	class CSkinModelDataResources{
	public:
		/*!
		 * @brief	コンストラクタ。
		 */
		CSkinModelDataResources();
		/*!
		 * @brief	デストラクタ。
		 */
		~CSkinModelDataResources();
		/*!
		 * @brief	ロード。
		 *@param[out]	skinModelDataHandle	スキンモデルデータのハンドルの格納先。
		 *@param[in]	modelPath			モデルのファイルパス。
		 *@param[in]	anim				アニメーション。
		 *@param[in]	isInstancing		インスタンシングモデル？
		 *@param[in]	numInstance			インスタンスの数。
		 */
		void Load(
			CSkinModelDataHandle& skinModelDataHandle,
			const char* modelPath,
			CAnimation* anim,
			bool isInstancing ,
			int numInstance 
		);
		/*!
		* @brief	非同期読み込み
		* @details
		*  この関数を使用する場合はCSkinModelDataHandleのIsLoadEnd関数を使用して同期を取ってください。
		*@param[out]	skinModelDataHandle	スキンモデルデータのハンドルの格納先。
		*@param[in]	modelPath			モデルのファイルパス。
		*@param[in]	anim				アニメーション。
		*@param[in]	isInstancing		インスタンシングモデル？
		*@param[in]	numInstance			インスタンスの数。
		*/
		void LoadAsync(
			CSkinModelDataHandle& skinModelDataHandle,
			const char* modelPath,
			CAnimation* anim,
			bool isInstancing,
			int numInstance
			)
		{
			
			m_asyncLoadReqeustQueueCS.Lock();
			//非同期読み込みのリクエストを作成してキューに積む。
			SAsyncLoadRequest req;
			req.skindModelDataHandle = &skinModelDataHandle;
			req.modelPath = modelPath;
			req.anim = anim;
			req.isInstancing = isInstancing;
			req.numInstance = numInstance;
			m_asyncLoadRequestQueue.push(req);
			//キューに積まれたので寝ているワーカースレッドを起こす。
			m_asyncLoadReqeustQueueCS.Unlock();
		}
		/*!
		* @brief	更新。
		*/
		void Update();
		/*!
		* @brief	非同期読み込みスレッドから呼ばれる更新関数。
		*/
		void UpdateAsyncLoadThread();
		/*!
		* @brief	CSkinModelDataのリリースを破棄。
		*/
		void Release()
		{
			m_cs.Lock();
			m_instancingModelDataList.clear();
			m_skinModelDataMap.clear();
			m_cs.Unlock();
		}
		/*!
		* @brief	ガベージコレクトの実行。
		*@details
		* 参照カウンタがになっているCSkinModelDataが解放されます。
		*/
		void GC();
	private:
		/*!
		 * @brief	非同期読み込みリクエスト
		 */
		struct SAsyncLoadRequest{
			CSkinModelDataHandle*	skindModelDataHandle;
			std::string modelPath;
			CAnimation* anim;
			bool isInstancing;
			int numInstance;
		};
		typedef std::map<int, CSkinModelDataPtr >	CSkinModelDataMap;
		typedef std::list<CSkinModelDataPtr>		CSkinModelDataList;
		CSkinModelDataMap	m_skinModelDataMap;
		CSkinModelDataList	m_instancingModelDataList;
		std::queue<SAsyncLoadRequest> m_asyncLoadRequestQueue;	//!<非同期読み込みリクエストのキュー。
		CCriticalSection m_asyncLoadReqeustQueueCS;				//!<読み込みリクエストキューを守るクリティカルセクション。
		CCriticalSection m_cs;
		std::thread m_asyncLoadThread;							//!<非同期読み込みスレッド。
	};
}