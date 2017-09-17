/*!
 *@brief	スキンモデルデータ。
 */

#pragma once

#include "tkEngine/graphics/tkSkeleton.h"

namespace tkEngine{
	class CAnimationClip;
	typedef std::unique_ptr<CAnimationClip>	CAnimationClipPtr;
	class CModelEffect : public DirectX::IEffect {
	protected:
		std::wstring m_materialName;	//!<マテリアル名。
		CShader m_vsShader;
		CShader m_psShader;
		ID3D11ShaderResourceView* m_diffuseTex = nullptr;
		ID3D11ShaderResourceView* m_normalMap = nullptr;
		ID3D11ShaderResourceView* m_specularMap = nullptr;
		bool isSkining;
		/*!
		* @brief	マテリアルパラメータ。
		*/
		struct MaterialParam {
			int hasNormalMap;		//!<法線マップある？
			int hasSpecularMap;		//!<スペキュラマップある？
			float anisotropic;		//!<異方性反射。
		};
		static const int NUM_POINT_LIGHT = 1024;
		MaterialParam m_materialParam;				//マテリアルパラメータ。
		CConstantBuffer m_materialParamCB;			//マテリアルパラメータ用の定数バッファ。
	public:
		CModelEffect()
		{
			m_materialParam.anisotropic = 0.5f;
			m_materialParamCB.Create(&m_materialParam, sizeof(m_materialParam));
		}
		void __cdecl Apply(ID3D11DeviceContext* deviceContext) override
		{
			
			deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShader.GetBody(), NULL, 0);
			deviceContext->PSSetShader((ID3D11PixelShader*)m_psShader.GetBody(), NULL, 0);
			deviceContext->PSSetShaderResources(0, 1, &m_diffuseTex);
			m_materialParam.hasNormalMap = 0;
			static int hoge = 1 ;
			if (m_normalMap != nullptr) {
				deviceContext->PSSetShaderResources(1, 1, &m_normalMap);
				m_materialParam.hasNormalMap = hoge;
			}
			m_materialParam.hasSpecularMap = 0;
			if (m_specularMap != nullptr) {
				deviceContext->PSSetShaderResources(2, 1, &m_specularMap);
				m_materialParam.hasSpecularMap = 1;
			}
			deviceContext->UpdateSubresource(m_materialParamCB.GetBody(), 0, NULL, &m_materialParam, 0, 0);
			deviceContext->PSSetConstantBuffers(2, 1, &m_materialParamCB.GetBody());

		}

		void __cdecl GetVertexShaderBytecode(void const** pShaderByteCode, size_t* pByteCodeLength) override
		{
			*pShaderByteCode = m_vsShader.GetByteCode();
			*pByteCodeLength = m_vsShader.GetByteCodeSize();
		}
		void SetDiffuseTexture(ID3D11ShaderResourceView* tex)
		{
			m_diffuseTex = tex;
		}
		void SetNormalMap(ID3D11ShaderResourceView* tex)
		{
			m_normalMap = tex;
		}
		void SetSpecularMap(ID3D11ShaderResourceView* tex)
		{
			m_specularMap = tex;
		}
		void SetMatrialName(const wchar_t* matName)
		{
			m_materialName = matName;
		}
		bool EqualMaterialName(const wchar_t* name) const
		{
			return wcscmp(name, m_materialName.c_str()) == 0;
		}
	};
	/*!
	*@brief
	*  スキンなしモデルエフェクト。
	*/
	class CNonSkinModelEffect : public CModelEffect {
	public:
		CNonSkinModelEffect()
		{
			m_vsShader.Load("Assets/shader/model.fx", "VSMain", CShader::EnType::VS);
			m_psShader.Load("Assets/shader/model.fx", "PSMain", CShader::EnType::PS);
			isSkining = false;
		}
	};
	/*!
	*@brief
	*  スキンモデルエフェクト。
	*/
	class CSkinModelEffect : public CModelEffect {
	public:
		CSkinModelEffect()
		{
			m_vsShader.Load("Assets/shader/model.fx", "VSMainSkin", CShader::EnType::VS);
			m_psShader.Load("Assets/shader/model.fx", "PSMain", CShader::EnType::PS);
			isSkining = true;
		}
	};

	/*!
	 *@brief	スキンモデルデータ。
	 */
	class CSkinModelData : Noncopyable{
	public:
		
		/*!
		 *@brief	コンストラクタ。
		 */
		CSkinModelData();
		/*!
		 *@brief	デストラクタ。
		 */
		~CSkinModelData();
		/*!
		 *@brief	ロード。
		 *@param[in]	filePath	ファイルパス。
		 *@return	trueが返ってきたらロード成功。
		 */
		bool Load( const wchar_t* filePath );
		DirectX::Model& GetBody()
		{
			return *m_modelDx;
		}
		/*!
		 *@brief	スケルトンを取得。
		 */
		CSkeleton& GetSkeleton()
		{
			return m_skeleton;
		}
		typedef std::function<void(std::unique_ptr<DirectX::ModelMeshPart>&)>		OnFindMesh;
		/*!
		 *@brief	メッシュの検索。
		 *@param[in]	findMesh		メッシュを見つけた時に呼ばれるコールバック関数
		 */
		void FindMesh(OnFindMesh findMesh);
	private:
		
		std::unique_ptr<DirectX::Model> m_modelDx;
		CSkeleton	m_skeleton;
	};
}