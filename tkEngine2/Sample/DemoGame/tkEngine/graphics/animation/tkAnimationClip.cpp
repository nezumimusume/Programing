/*!
 *@brief	アニメーションクリップ。
 */

#include "tkEngine/tkEnginePrecompile.h"
#include "tkEngine/graphics/animation/tkAnimationClip.h"

namespace tkEngine {
	/*!
	*@brief
	*/
	CAnimationClip::~CAnimationClip()
	{
	}
	/*!
	*@brief	アニメーションクリップをロード。
	*@param[in]	filePath	ファイルパス。
	*@param[in]	clipName	クリップ名。
	*/
	void CAnimationClip::Load(const wchar_t* filePath, const wchar_t* clipName)
	{
		FILE* fp = _wfopen(filePath, L"rb");
		if (fp == nullptr) {
			TK_WARNING("ファイルのオープンに失敗しました。: CAnimationClip::Load");
			return;
		}
		if (clipName != nullptr) {
			m_clipName = clipName;
		}
		//キーの数を取得する。
		int numKey;
		fread(&numKey, sizeof(numKey), 1, fp);
		//中身をごそっとロード。
		std::unique_ptr<KeyframeRow[]> keyframes;
		keyframes = std::make_unique<KeyframeRow[]>(numKey);
		fread(keyframes.get(), sizeof(KeyframeRow), numKey, fp);
		fclose(fp);
		for (int i = 0; i < numKey; i++) {
			KeyframePtr keyframe = std::make_unique<Keyframe>();
			keyframe->boneIndex = keyframes[i].boneIndex;
			keyframe->transform = CMatrix::Identity;
			keyframe->time = keyframes[i].time;
			for (int j = 0; j < 4; j++) {
				keyframe->transform.m[j][0] = keyframes[i].transform[j].x;
				keyframe->transform.m[j][1] = keyframes[i].transform[j].y;
				keyframe->transform.m[j][2] = keyframes[i].transform[j].z;
			}
			m_keyframes.push_back(std::move(keyframe));
		}

		//ボーンインデックスごとのキーフレームの連結リストを作成する。
		m_keyFramePtrListArray.resize(MAX_BONE);
		for (auto& keyframe : m_keyframes) {
			m_keyFramePtrListArray[keyframe->boneIndex].push_back(keyframe.get());
			if (m_topBoneKeyFramList == nullptr) {
				m_topBoneKeyFramList = &m_keyFramePtrListArray[keyframe->boneIndex];
			}
		}
	}
}

