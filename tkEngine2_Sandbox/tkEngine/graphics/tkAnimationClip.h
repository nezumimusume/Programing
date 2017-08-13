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
	 *@brief	アニメーションクリップ。
	 */
	class CAnimationClip : Noncopyable{
	public:
		typedef std::vector<Keyframe*>		keyFramePtrList;
		/*!
		 * @brief	コンストラクタ
		 *@param[in]	clipName	クリップ名。
		 *@param[in]	clip		アニメーションクリップ。
		 *@param[in]	keyFrames	キーフレーム。
		 *@param[in]	baseBoneNo	基本ボーン番号。
		 */
		CAnimationClip(
			const wchar_t* clipName,
			const VSD3DStarter::Clip* clip,
			const VSD3DStarter::Keyframe* keyFrames
		);
		/*!
		 *@brief	デストラクタ。
		 */
		~CAnimationClip();
		/*!
		*@brief	キーフレームを追加。
		*/
		void AddKeyFrame(int numKeyframes, const VSD3DStarter::Keyframe* keyFrames, int baseBoneNo);
		/*!
		 *@brief
		 */
		const std::vector<keyFramePtrList>& GetKeyFramePtrListArray() const
		{
			return m_keyFramePtrListArray;
		}
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
	private:
		
		std::wstring m_name;	//!<クリップの名前。
		float m_startTime;		//!<開始時間。
		float m_endTime;		//!<終了時間。
		unsigned int m_numKeys;	//!<キーフレームの数。
		bool m_isLoop = false;	//!<ループフラグ。
		typedef std::unique_ptr<Keyframe> KeyframePtr;
		std::vector<KeyframePtr>	m_keyframes;	//キーフレーム。
		std::vector<keyFramePtrList>	m_keyFramePtrListArray;	//ボーンごとのキーフレームのリストを管理するための配列。
	};
	typedef std::unique_ptr<CAnimationClip>	CAnimationClipPtr;
}