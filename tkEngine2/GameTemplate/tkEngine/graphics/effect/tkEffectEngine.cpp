/*!
 * @brief	エフェクトエンジン。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/effect/tkEffectEngine.h"

namespace tkEngine {
	CEffectEngine::CEffectEngine()
	{
	}
	CEffectEngine::~CEffectEngine()
	{
		Release();
	}

	void CEffectEngine::Release()
	{
		if (m_manager != nullptr) {
			m_manager->Destroy();
			m_manager = nullptr;
		}
		if (m_renderer != nullptr) {
			m_renderer->Destroy();
			m_renderer = nullptr;
		}
	}
	void CEffectEngine::Init()
	{
		Release();
		//レンダラーを初期化。
		m_renderer = EffekseerRendererDX11::Renderer::Create(
			GraphicsEngine().GetD3DDevice(),
			GraphicsEngine().GetD3DDeviceContext(),
			2000);
		//エフェクトマネージャを初期化。
		m_manager = Effekseer::Manager::Create(2000);

		// 描画用インスタンスから描画機能を設定
		m_manager->SetSpriteRenderer(m_renderer->CreateSpriteRenderer());
		m_manager->SetRibbonRenderer(m_renderer->CreateRibbonRenderer());
		m_manager->SetRingRenderer(m_renderer->CreateRingRenderer());
		m_manager->SetTrackRenderer(m_renderer->CreateTrackRenderer());
		m_manager->SetModelRenderer(m_renderer->CreateModelRenderer());

		// 描画用インスタンスからテクスチャの読込機能を設定
		// 独自拡張可能、現在はファイルから読み込んでいる。
		m_manager->SetTextureLoader(m_renderer->CreateTextureLoader());
		m_manager->SetModelLoader(m_renderer->CreateModelLoader());
	}
	
	Effekseer::Effect* CEffectEngine::CreateEffekseerEffect(const wchar_t* filePath)
	{
		return Effekseer::Effect::Create(m_manager, (const EFK_CHAR*)filePath);
	}
	Effekseer::Handle CEffectEngine::Play(Effekseer::Effect* effect )
	{
		return m_manager->Play(effect, 0, 0, 0);
	}
	void CEffectEngine::Stop(Effekseer::Handle handle)
	{
		m_manager->StopEffect(handle);
	}
	void CEffectEngine::Update()
	{
		//カメラ行列を設定。
		m_renderer->SetCameraMatrix(MainCamera().GetViewMatrix());
		m_renderer->SetProjectionMatrix(MainCamera().GetProjectionMatrix());

		m_manager->Update(GameTime().GetFrameDeltaTime() / (1.0f / 60.0f));
	}
	void CEffectEngine::Render(CRenderContext& rc)
	{
		BeginGPUEvent(L"enRenderStep_RenderEffect");
		//レンダリングステップを3Dモデルの描画に。
		rc.SetRenderStep(enRenderStep_RenderEffect);
		m_renderer->BeginRendering();
		m_manager->Draw();
		m_renderer->EndRendering();
		EndGPUEvent();
	}
}