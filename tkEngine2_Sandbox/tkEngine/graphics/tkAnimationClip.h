/*!
 *@brief	アニメーションクリップ。
 */

#pragma once

namespace tkEngine{
	/*!
	 *@brief	キーフレーム。
	 */
	struct Keyframe {
		unsigned int boneIndex;		//!<ボーンインデックス。
		float time;					//!<時間。
		CMatrix transform;			//!<トランスフォーム。
	};
	/*!
	*@brief	キーフレーム。
	*/
	struct KeyframeRow {
		unsigned int boneIndex;		//!<ボーンインデックス。
		CVector3 transform[4];		//!<トランスフォーム。
	};
	/*!
	 *@brief	アニメーションクリップ。
	 */
	class CAnimationClip : Noncopyable {
	public:
		typedef std::vector<Keyframe*>		keyFramePtrList;
		/*!
		 * @brief	コンストラクタ
		 *@details
		 * 削除予定。
		 *@param[in]	clipName	クリップ名。
		 *@param[in]	clip		アニメーションクリップ。
		 *@param[in]	keyFrames	キーフレーム。
		 *@param[in]	baseBoneNo	基本ボーン番号。
		 */
		CAnimationClip(
			const wchar_t* clipName,
			const VSD3DStarter::Clip* clip,
			const VSD3DStarter::Keyframe* keyFrames,
			int baseBoneNo,
			std::vector<int> localBoneIDtoGlobalBoneIDTbl
		);
		/*!
		* @brief	コンストラクタ
		*/
		CAnimationClip() {}
		/*!
		 *@brief	デストラクタ。
		 */
		~CAnimationClip();
		/*!
		 *@brief	アニメーションクリップをロード。
		 *@param[in]	filePath	ファイルパス。
		 */
		void Load(const wchar_t* filePath);
		/*!
		*@brief	キーフレームを追加。
		*/
		void AddKeyFrame(
			int numKeyframes,
			const VSD3DStarter::Keyframe* keyFrames,
			int baseBoneNo,
			const std::vector<int>& localBoneIDtoGlobalBoneIDTbl
		);
		
		/*!
		*@brief	名前を取得。
		*/
		const std::wstring& GetName() const
		{
			return m_name;
		}
		/*!
		*@brief	ループする？
		*/
		bool IsLoop() const
		{
			return m_isLoop;
		}
		/*!
		*@brief	ループフラグを設定する。
		*/
		void SetLoopFlag(bool flag)
		{
			m_isLoop = flag;
		}
		/*!
		*@brief
		*/
		const std::vector<keyFramePtrList>& GetKeyFramePtrListArray() const
		{
			return m_keyFramePtrListArray;
		}
		const keyFramePtrList& GetTopBoneKeyFrameList() const
		{
			return *m_topBoneKeyFramList;
		}
	private:
		
		std::wstring m_name;	//!<クリップの名前。
		float m_startTime;		//!<開始時間。
		float m_endTime;		//!<終了時間。
		unsigned int m_numKeys;	//!<キーフレームの数。
		bool m_isLoop = false;	//!<ループフラグ。
		typedef std::unique_ptr<Keyframe> KeyframePtr;
		std::vector<KeyframePtr>	m_keyframes;	//キーフレーム。
		std::vector<keyFramePtrList>	m_keyFramePtrListArray;	//ボーンごとのキーフレームのリストを管理するための配列。
		keyFramePtrList*				m_topBoneKeyFramList = nullptr;
	};
	typedef std::unique_ptr<CAnimationClip>	CAnimationClipPtr;
}