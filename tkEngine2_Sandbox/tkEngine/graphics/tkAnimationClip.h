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
		float time;					//!<時間。
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
		*/
		CAnimationClip() {}
		/*!
		 *@brief	デストラクタ。
		 */
		~CAnimationClip();
		/*!
		 *@brief	アニメーションクリップをロード。
		 *@param[in]	filePath	ファイルパス。
		 *@param[in]	clipName	クリップ名。
		 */
		void Load(const wchar_t* filePath, const wchar_t* cliipName);
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
		/*!
		 *@brief	クリップ名を取得。
		 */
		const wchar_t* GetName() const
		{
			return m_clipName.c_str();
		}
	private:
		std::wstring m_clipName;	//!<アニメーションクリップの名前。
		bool m_isLoop = false;	//!<ループフラグ。
		typedef std::unique_ptr<Keyframe> KeyframePtr;
		std::vector<KeyframePtr>	m_keyframes;	//キーフレーム。
		std::vector<keyFramePtrList>	m_keyFramePtrListArray;	//ボーンごとのキーフレームのリストを管理するための配列。
		keyFramePtrList*				m_topBoneKeyFramList = nullptr;
	};
	typedef std::unique_ptr<CAnimationClip>	CAnimationClipPtr;
}