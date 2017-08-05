/*!
 * @brief	ライトの管理者。
 */

#pragma once

namespace tkEngine{
	class CDirectionLight;
	class CPointLight;
	class CLightBase;
	/*!
	 * @brief	ライトの管理者
	 * @details
	 *  インスタンス化されたCLightBaseのインスタンスはすべてCLightManagerに登録されます。
	 *  このクラスのインスタンスはCEngineクラスのみが保持しており、その他のクラスでインスタンスを生成することはできません。
	 */
	class CLightManager{
	friend class CEngine;
	private:
		CLightManager();
		~CLightManager();
	public:
		void Init();
		void AddLight(CLightBase* light);
		void RemoveLight(CLightBase* light);
		void Update();
	private:
		
		std::list<CDirectionLight*>		m_directionLights;		//!<平行光源のリスト。
		CStructuredBuffer				m_directionLightSB;		//!<平行光源のリストのストラクチャーバッファ。
		CShaderResourceView				m_directionLightSRV;	//!<平行光源のリストのSRV。
		std::list<CPointLight*>			m_pointLights;			//!<ポイントライトのリスト。
		CStructuredBuffer				m_pointLightsSB;		//!<ポイントライトのリストのストラクチャーバッファ。
		CShaderResourceView				m_pointLightsSRV;		//!<ポイントライトのリストのSRV。
	};
}