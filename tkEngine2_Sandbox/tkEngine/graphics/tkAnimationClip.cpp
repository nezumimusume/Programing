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
		m_keyframes.resize(m_numKeys);
		unsigned int boneIDMax = 0;
		for (int i = 0; i < m_numKeys; i++) {
			Keyframe& keyframe = m_keyframes.at(i);
			keyframe.boneIndex = keyFrames[i].BoneIndex;
			keyframe.time = keyFrames[i].Time;
			keyframe.transform = keyFrames[i].Transform;
			boneIDMax = max(boneIDMax, keyframe.boneIndex);
		}
		//ボーンインデックスごとのキーフレームの連結リストを作成する。
		m_keyFramePtrListArray.resize(boneIDMax+1);
		for (auto& keyframe : m_keyframes) {
			m_keyFramePtrListArray[keyframe.boneIndex].push_back(&keyframe);
		}

	}
	/*!
	*@brief
	*/
	CAnimationClip::~CAnimationClip()
	{
	}
}

