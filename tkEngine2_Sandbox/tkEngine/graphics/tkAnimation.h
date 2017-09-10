/*!
 * @brief	アニメーション
 */

#pragma once

#include "tkEngine/graphics/tkAnimationClip.h"

namespace tkEngine{
	
	class CSkeleton;
	/*!
	 * @brief	アニメーションクラス。
	 */
	class CAnimation {
	public:
		CAnimation();
		~CAnimation();
		/*!
		 *@brief	初期化。
		 *@param[in]	skinModelData	スキンモデルデータ、
		 *@param[in]	animeClipList	アニメーションクリップのリスト。
		 *@param[in]	numAnimClip		アニメーションクリップの数。
		 */
		void Init(CSkinModelData& skinModelData, CAnimationClip* animClipList[], int numAnimClip);
		/*!
		* @brief	アニメーションを進める。
		*@param[in]	deltaTime		アニメーションを進める時間(単位：秒)。
		*/
		void Update(float deltaTime);
		/*!
		 *@brief	アニメーションの再生。
		 *@param[in]	clipName	アニメーションクリップの名前。
		 */
		void Play(const wchar_t* clipName)
		{
			if (clipName == nullptr) {
				TK_WARNING("clipName is NULL");
				return;
			}
			auto it = std::find_if(
				m_animationClips.begin(),
				m_animationClips.end(), 
				[clipName](auto& clip) {
					return wcscmp(clip->GetName(), clipName ) == 0;
				}
			);
			if (it == m_animationClips.end()) {
				TK_WARNING("not found clip");
				return;
			}
			
			PlayCommon(*it);
		}
		/*!
		*@brief	アニメーションの再生。
		*@param[in]	clipNo	アニメーションクリップの番号。Init関数に渡したanimClipListの並びとなる。
		*/
		void Play(int clipNo)
		{
			PlayCommon(m_animationClips[clipNo]);
		}
		/*!
		*@brief	アニメーションクリップのループフラグを設定します。
		*@param[in]	clipName	アニメーションクリップの名前。
		*@param[in]	flag		フラグ。
		*/
		void SetAnimationClipLoopFlag(const wchar_t* clipName, bool flag)
		{
			auto it = std::find_if(
				m_animationClips.begin(),
				m_animationClips.end(),
				[clipName](auto& clip) {return clip->GetName() == clipName; }
			);
			if (it == m_animationClips.end()) {
				//見つからなかった。
				return ;
			}
			(*it)->SetLoopFlag(flag);
		}
	private:
		void PlayCommon(CAnimationClip* nextClip)
		{
			m_currentAnimationClip = nextClip;
			m_globalTime = 0.0f;
			m_currentKeyframeNo = 0;
		}
	private:
		std::vector<CAnimationClip*>	m_animationClips;	//!<アニメーションクリップの配列。
		CSkeleton* m_skeleton = nullptr;	//!<アニメーションを適用するスケルトン。
		CAnimationClip* m_currentAnimationClip = nullptr;	//!<現在再生中のアニメーションクリップ。
		float m_globalTime = 0.0f;
		int m_currentKeyframeNo = 0;		//!<現在再生中のアニメーションキーフレーム番号。
		
	};
}