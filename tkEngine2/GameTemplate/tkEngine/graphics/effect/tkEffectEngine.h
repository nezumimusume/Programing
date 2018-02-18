/*!
 * @brief	エフェクトエンジン。
 */

#pragma once

namespace tkEngine{
	/*!
	 * @brief	エフェクトエンジン。
	 */
	class CEffectEngine : Noncopyable{
	public:
		CEffectEngine();
		~CEffectEngine();
		/*!
		 *@brief	解放。
		 */
		void Release();
		/*!
		 *@brief	初期化。
		 */
		void Init();
		/*!
		 *@brief	更新。
		 */
		void Update();
		/*!
		 *@brief	描画。
		 */
		void Render(CRenderContext& rc);
		/*!
		 *@brief	Effekseerのエフェクトを作成。
		 */
		Effekseer::Effect* CreateEffekseerEffect(const wchar_t* filePath);
		/*!
		 *@brief	Effekseerのエフェクトを再生。
		 */
		Effekseer::Handle Play(Effekseer::Effect* effect);
		/*!
		 *@brief	Effekseerマネージャの取得。
		 */
		Effekseer::Manager& GetEffekseerManager()
		{
			return *m_manager;
		}
		/*!
		 *@brief	Effekseerのエフェクトの停止。
		 */
		void Stop(Effekseer::Handle handle);
	private:
		Effekseer::Manager*	m_manager= nullptr;
		EffekseerRenderer::Renderer*	m_renderer = nullptr;
	};
}