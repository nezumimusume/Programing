/*!
 *@brief	スキンモデルデータ。
 */

#pragma once

#include "tkEngine/graphics/tkSkeleton.h"

namespace tkEngine{
	class CAnimationClip;
	typedef std::unique_ptr<CAnimationClip>	CAnimationClipPtr;
	/*!
	*@brief	モデルエフェクト。
	*/
	class CModelEffect : public DirectX::IEffect {
	protected:
		std::wstring m_materialName;	//!<マテリアル名。
		CShader m_vsShader;
		CShader m_psShader;
		CShader m_vsRenderToDepthShader;	//!<Z値書き込み用の頂点シェーダー。
		CShader m_psRenderToDepthShader;	//!<Z値書き込み用のピクセルシェーダー。
		ID3D11ShaderResourceView* m_diffuseTex = nullptr;
		ID3D11ShaderResourceView* m_normalMap = nullptr;
		ID3D11ShaderResourceView* m_specularMap = nullptr;
		bool isSkining;
		/*!
		* @brief	マテリアルパラメータ。
		* @details 
		* こいつを変更する場合は、modelCB.hのMaterialParamCbも変更するように。
		*/
		struct MaterialParam {
			int hasNormalMap;		//!<法線マップある？
			int hasSpecularMap;		//!<スペキュラマップある？
			float anisotropic;		//!<異方性反射。
		};
		static const int NUM_POINT_LIGHT = 1024;
		MaterialParam m_materialParam;				//マテリアルパラメータ。
		CConstantBuffer m_materialParamCB;			//マテリアルパラメータ用の定数バッファ。
		CRenderContext* m_renderContext = nullptr;	//レンダリングコンテキスト。
	public:
		CModelEffect()
		{
			m_materialParam.anisotropic = 0.5f;
			m_materialParamCB.Create(&m_materialParam, sizeof(m_materialParam));
			m_psShader.Load("Assets/shader/model.fx", "PSMain", CShader::EnType::PS);
			m_psRenderToDepthShader.Load("Assets/shader/model.fx", "PSMain_RenderDepth", CShader::EnType::PS);
		}
		void __cdecl Apply(ID3D11DeviceContext* deviceContext) override;
		
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
		void SetRenderContext(CRenderContext& rc)
		{
			m_renderContext = &rc;
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
			m_vsRenderToDepthShader.Load("Assets/shader/model.fx", "VSMain_RenderDepth", CShader::EnType::VS);
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
			m_vsRenderToDepthShader.Load("Assets/shader/model.fx", "VSMainSkin_RenderDepth", CShader::EnType::VS);
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
		typedef std::function<void(CModelEffect*)>	OnFindModelEffect;
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