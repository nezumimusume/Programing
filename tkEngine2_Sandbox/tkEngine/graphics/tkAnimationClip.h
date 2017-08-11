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
		/*!
		 * @brief	コンストラクタ
		 *@param[in]	clipName	クリップ名。
		 *@param[in]	clip		アニメーションクリップ。
		 *@param[in]	keyFrames	キーフレーム。
		 */
		CAnimationClip(
			const wchar_t* clipName,
			const VSD3DStarter::Clip* clip,
			const VSD3DStarter::Keyframe* keyFrames
		);
		/*!
		 *@brief
		 */
		~CAnimationClip();
	private:
		typedef std::list<Keyframe*>		keyFramePtrList;
		float m_startTime;		//!<開始時間。
		float m_endTime;		//!<終了時間。
		unsigned int m_numKeys;	//!<キーフレームの数。
		std::vector<Keyframe>	m_keyframes;	//キーフレーム。
		std::vector<keyFramePtrList>	m_keyFramePtrListArray;
	};
}
