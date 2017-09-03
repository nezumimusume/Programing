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
		const VSD3DStarter::Keyframe* keyFrames,
		int baseBoneNo,
		std::vector<int> localBoneIDtoGlobalBoneIDTbl
	)
	{
		m_name = clipName;
		m_startTime = clip->StartTime;
		m_endTime = clip->EndTime;
		//m_keyframes.resize(m_numKeys);
		for (int i = 0; i < clip->keys; i++) {
			KeyframePtr keyframe = std::make_unique<Keyframe>();
			int localBoneIndex = keyFrames[i].BoneIndex + baseBoneNo;
			keyframe->boneIndex = localBoneIDtoGlobalBoneIDTbl[localBoneIndex];
			keyframe->time = keyFrames[i].Time;
			keyframe->transform = keyFrames[i].Transform;
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
	/*!
	*@brief
	*/
	CAnimationClip::~CAnimationClip()
	{
	}
	/*!
	*@brief	アニメーションクリップをロード。
	*@param[in]	filePath	ファイルパス。
	*/
	void CAnimationClip::Load(const wchar_t* filePath)
	{
		FILE* fp = _wfopen(filePath, L"rb");
		if (fp == nullptr) {
			TK_WARNING("ファイルのオープンに失敗しました。: CAnimationClip::Load");
			return;
		}
		//キーの数を取得する。
		int numKey;
		fread(&numKey, sizeof(numKey), 1, fp);
		//中身をごそっとロード。
		std::unique_ptr<KeyframeRow[]> keyframes;
		keyframes = std::make_unique<KeyframeRow[]>(numKey);
		fread(keyframes.get(), sizeof(KeyframeRow), numKey, fp);
		fclose(fp);
	}
	
	/*!
	*@brief	キーフレームを追加。
	*/
	void CAnimationClip::AddKeyFrame(
		int numKey, 
		const VSD3DStarter::Keyframe* keyFrames, 
		int baseBoneNo,
		const std::vector<int>& localBoneIDtoGlobalBoneIDTbl
	)
	{
		for (int i = 0; i < numKey; i++) {
			KeyframePtr keyframe = std::make_unique<Keyframe>();
			int localBoneID = keyFrames[i].BoneIndex + baseBoneNo;
			keyframe->boneIndex = localBoneIDtoGlobalBoneIDTbl[localBoneID];
			keyframe->time = keyFrames[i].Time;
			keyframe->transform = keyFrames[i].Transform;
			m_keyFramePtrListArray[keyframe->boneIndex].push_back(keyframe.get());
			m_numKeys = m_keyFramePtrListArray[keyframe->boneIndex].size();
			m_keyframes.push_back(std::move(keyframe));
			
		}
	}
}

