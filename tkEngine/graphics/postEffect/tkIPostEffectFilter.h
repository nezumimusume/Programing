/*!
 * @brief	フィルターの基底クラス。
 */

#pragma once

namespace tkEngine{
	class CPostEffect;
	typedef void(*DrawSkinModelMaskFunc)(CRenderContext& renderContext);
	class IPostEffectFilter : Noncopyable{
	public:
		void Render( CRenderContext& renderContext, CPostEffect* postEffect );
		void SetEnalbe(bool flag) {
			m_isEnable = flag;
		}
		void SetBlendRate(float rate)
		{
			m_blendRate = rate;
		}
		float GetBlendRate() const
		{
			return m_blendRate;
		}
		void RegistMaskSkinModel(DrawSkinModelMaskFunc pFunc)
		{
			maskModelsFunc.push_back(pFunc);
		}
	protected:
		CEffect*	m_effect = nullptr;
		bool		m_isEnable = false;
		float		m_blendRate = 0.0f;	//ブレンド率。1.0で完全にセピアになります。
		std::vector<DrawSkinModelMaskFunc>	maskModelsFunc;		//マスクモデル。
		CRenderTarget m_clearRenderTarget;
	};

}