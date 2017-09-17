/*!
 * @brief	ライトの管理者。
 */

#include "tkEngine/tkEnginePrecompile.h"
#include "tkEngine/light/tkLightManager.h"
#include "tkEngine/light/tkPointLight.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "tkEngine/graphics/prerender/tkLightCulling.h"

namespace tkEngine{
	using namespace prefab;
	CLightManager::CLightManager()
	{
	}
	CLightManager::~CLightManager()
	{
	}
	void CLightManager::Init()
	{
		InitDirectionLightStructuredBuffer();
		InitPointLightStructuredBuffer();
		InitPointLightInTileStructuredBuffer();
		SetAmbientLight({ 0.5f, 0.5f, 0.5f });
		m_lightParamCB.Create(&m_lightParam, sizeof(m_lightParam));
		
	}
	void CLightManager::InitPointLightInTileStructuredBuffer()
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		//タイルの数
		int numTile = (GraphicsEngine().GetFrameBufferWidth() / CLightCulling::TILE_WIDTH)
			* (GraphicsEngine().GetFrameBufferHeight() / CLightCulling::TILE_WIDTH);
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;	//SRVとUAVにバインド可能。
		desc.ByteWidth = sizeof(unsigned int) * MAX_POINT_LIGHT * numTile;
		desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		desc.StructureByteStride = sizeof(unsigned int);
		m_pointLightsInTileSB.Create(NULL, desc);
	}
	void CLightManager::InitDirectionLightStructuredBuffer()
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		int stride = sizeof(SDirectionLight);

		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;	//SRVとしてバインド可能。
		desc.ByteWidth = stride * MAX_DIRECTION_LIGHT;
		desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		desc.StructureByteStride = stride;

		m_directionLightSB.Create(NULL, desc);
	}
	void CLightManager::InitPointLightStructuredBuffer()
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		int stride = sizeof(SPointLight);

		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;	//SRVとしてバインド可能。
		desc.ByteWidth = stride * MAX_POINT_LIGHT;
		desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		desc.StructureByteStride = stride;

		m_pointLightsSB.Create(NULL, desc);
	}
	void CLightManager::AddLight(CLightBase* light)
	{
		if (m_pointLights.size() >= MAX_POINT_LIGHT) {
			TK_WARNING("m_pointLights.size() is full!!");
			return;
		}
		if (m_directionLights.size() >= MAX_DIRECTION_LIGHT) {
			TK_WARNING("m_directionLights.size() is full!!");
			return;
		}
		//ライトの振り分け。
		const std::type_info& typeInfo = typeid(*light);
		if (typeInfo == typeid(CPointLight)) {
			//登録済みか調べる。
			auto findIt = std::find(m_pointLights.begin(), m_pointLights.end(), light);
			if (findIt == m_pointLights.end()) {
				//新規登録。
				m_pointLights.push_back(reinterpret_cast<CPointLight*>(light));
			}
			else {
				//既に登録されてるよ。
				TK_LOG("This light was already added");
				return;
			}
		}
		else if (typeInfo == typeid(prefab::CDirectionLight)) {
			//登録済みか調べる。
			auto findIt = std::find(m_directionLights.begin(), m_directionLights.end(), light);
			if (findIt == m_directionLights.end()) {
				//新規登録。
				m_directionLights.push_back(reinterpret_cast<CDirectionLight*>(light));
			}
			else {
				//既に登録されてるよ。
				TK_LOG("This light was already added");
				return;
			}
		}
		SetDirty();
	}
	void CLightManager::RemoveLight(CLightBase* light)
	{
		const std::type_info& typeInfo = typeid(*light);
		if (typeInfo == typeid(CPointLight)) {
			m_pointLights.erase(
				std::remove(m_pointLights.begin(), m_pointLights.end(), light), 
				m_pointLights.end()
			);
		}
		else if (typeInfo == typeid(CDirectionLight)) {
			m_directionLights.erase(
				std::remove(m_directionLights.begin(), m_directionLights.end(), light),
				m_directionLights.end()
			);
		}
		SetDirty();
	}
	void CLightManager::Update()
	{
		if (!m_isDirty) {
			//更新の必要なし。
			return;
		}
		//ディレクションライトのストラクチャーバッファを更新。
		int ligNo = 0;
		for (auto lig : m_directionLights) {
			m_rawDirectionLights[ligNo] = lig->GetRawData();
			ligNo++;
		}
		ligNo = 0;
		for (auto lig : m_pointLights) {
			m_rawPointLights[ligNo] = lig->GetRawData();
			ligNo++;
		}
		//ダーティフラグはここではおろさずに、Render関数でおろす。
		m_lightParam.eyePos = MainCamera().GetPosition();
		m_lightParam.numDirectionLight = m_directionLights.size();
		m_lightParam.numPointLight = m_pointLights.size();
	}
	void CLightManager::Render(CRenderContext& renderContext)
	{
		if (m_isDirty) {
			//StructuredBufferを更新する。
			renderContext.UpdateSubresource(m_directionLightSB, m_rawDirectionLights);
			renderContext.UpdateSubresource(m_pointLightsSB, m_rawPointLights);
			//ダーティフラグを下す。
			m_isDirty = false;
		}
		renderContext.UpdateSubresource(m_lightParamCB, &m_lightParam);
		//PSステージのtレジスタの100番目にディレクションライトのストラクチャーバッファを設定する。
		renderContext.PSSetShaderResource(100, m_directionLightSB.GetSRV());
		//PSステージのtレジスタの101番目にポイントライトのストラクチャーバッファを設定する。
		renderContext.PSSetShaderResource(101, m_pointLightsSB.GetSRV());
		//PSステージのtレジスタの102番目にタイルごとのポイントライトのインデックスリストのストラクチャーバッファを設定する。
		renderContext.PSSetShaderResource(102, m_pointLightsInTileSB.GetSRV());
		//PSステージのcレジスタの1番目にライト用の定数バッファを設定する。
		renderContext.PSSetConstantBuffer(1, m_lightParamCB);
	}
	/*!
	*@brief　１フレームの描画終了時に呼ばれる処理。
	*/
	void CLightManager::EndRender(CRenderContext& renderContext)
	{
		renderContext.PSUnsetShaderResource(100);
		renderContext.PSUnsetShaderResource(101);
		renderContext.PSUnsetShaderResource(102);
	}
}