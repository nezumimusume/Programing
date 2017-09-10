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
		 *@param[in]	clipName			アニメーションクリップの名前。
		 *@param[in]	interpolateTime		補完時間(単位：秒)
		 */
		void Play(const wchar_t* clipName, float interpolateTime = 0.0f)
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
			
			PlayCommon(*it, interpolateTime);
		}
		/*!
		*@brief	アニメーションの再生。
		*@param[in]	clipNo	アニメーションクリップの番号。Init関数に渡したanimClipListの並びとなる。
		*@param[in]	interpolateTime		補完時間(単位：秒)
		*/
		void Play(int clipNo, float interpolateTime = 0.0f)
		{
			PlayCommon(m_animationClips[clipNo], interpolateTime);
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
		void PlayCommon(CAnimationClip* nextClip, float interpolateTime)
		{
			if (interpolateTime != 0.0f) {
				//補完なし。
				m_currentAnimationClip = nextClip;
				m_globalTime = 0.0f;
				m_currentKeyframeNo = 0;
				//補完コントローラーをクリア。
				m_interpolateAnimationCtr.clear();
				
			}
			else {
				//新しい補完コントローラーを作成。
				SInterpolateAnimationControl ctr;
				ctr.clip = nextClip;
				ctr.interpolateTime = interpolateTime;
				ctr.interpolateRate = 0.0f;
				m_interpolateAnimationCtr.push_back(ctr);
			}
		}
	private:
		/*!
		 *@brief	アニメーション再生のリクエスト。
		 */
		struct SInterpolateAnimationControl {
			CAnimationClip*		clip;
			float				interpolateTime;		//!<補完時間。
			int					keyFrameNo;				//!<ローカルキーフレーム番号。
			float				interpolateRate;		//!<補完率。
		};
		std::vector<CAnimationClip*>	m_animationClips;	//!<アニメーションクリップの配列。
		CSkeleton* m_skeleton = nullptr;	//!<アニメーションを適用するスケルトン。
		CAnimationClip* m_currentAnimationClip = nullptr;	//!<現在再生中のアニメーションクリップ。
		std::vector<SInterpolateAnimationControl>	m_interpolateAnimationCtr;	//!<アニメーション補完のコントローラのキュー。
		float m_globalTime = 0.0f;
		int m_currentKeyframeNo = 0;		//!<現在再生中のアニメーションキーフレーム番号。
		
	};
}