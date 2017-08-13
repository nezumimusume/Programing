/*!
 *@brief	アニメーションクリップ。
 */

#include "tkEngine/tkEnginePrecompile.h"
#include "tkEngine/graphics/tkAnimationClip.h"

namespace tkEngine {
	/*!
	* @brief	コンストラクタ
	*@param[in]	clipName	クリップ名。
	*@param[in]	clip		アニメーションクリップ。
	*@param[in]	keyFrames	キーフレーム。
	*@param[in]	baseBoneNo	基本ボーン番号。
	*/
	CAnimationClip::CAnimationClip(
		const wchar_t* clipName,
		const VSD3DStarter::Clip* clip,
		const VSD3DStarter::Keyframe* keyFrames
	)
	{
		m_name = clipName;
		m_startTime = clip->StartTime;
		m_endTime = clip->EndTime;
		m_numKeys = clip->keys;
		//m_keyframes.resize(m_numKeys);
		for (int i = 0; i < m_numKeys; i++) {
			KeyframePtr keyframe = std::make_unique<Keyframe>();
			keyframe->boneIndex = keyFrames[i].BoneIndex;
			keyframe->time = keyFrames[i].Time;
			keyframe->transform = keyFrames[i].Transform;
			m_keyframes.push_back(std::move(keyframe));
		}
		//ボーンインデックスごとのキーフレームの連結リストを作成する。
		m_keyFramePtrListArray.resize(MAX_BONE);
		for (auto& keyframe : m_keyframes) {
			m_keyFramePtrListArray[keyframe->boneIndex].push_back(keyframe.get());
		}
	}
	/*!
	*@brief
	*/
	CAnimationClip::~CAnimationClip()
	{
	}
	/*!
	*@brief	キーフレームを追加。
	*/
	void CAnimationClip::AddKeyFrame(int numKey, const VSD3DStarter::Keyframe* keyFrames, int baseBoneNo)
	{
		for (int i = 0; i < numKey; i++) {
			KeyframePtr keyframe = std::make_unique<Keyframe>();
			keyframe->boneIndex = keyFrames[i].BoneIndex + baseBoneNo;
			keyframe->time = keyFrames[i].Time;
			keyframe->transform = keyFrames[i].Transform;
			m_keyFramePtrListArray[keyframe->boneIndex].push_back(keyframe.get());
			m_keyframes.push_back(std::move(keyframe));
			
		}
	}
}

