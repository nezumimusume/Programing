/*!
 *@brief	スキンモデルデータ
 */
#ifndef _TKSKINMODELDATA_H_
#define _TKSKINMODELDATA_H_


namespace tkEngine{
	struct D3DXFRAME_DERIVED : public D3DXFRAME {
		D3DXMATRIXA16	CombinedTransformationMatrix;	//合成済み行列。
	};
	struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER {
		LPDIRECT3DTEXTURE9* ppTextures;
		LPD3DXMESH pOrigMesh;
		LPD3DXATTRIBUTERANGE pAttributeTable;
		DWORD NumAttributeGroups;
		DWORD NumInfl;
		LPD3DXBUFFER pBoneCombinationBuf;
		D3DXMATRIX** ppBoneMatrixPtrs;
		D3DXMATRIX* pBoneOffsetMatrices;
		DWORD NumPaletteEntries;
		bool UseSoftwareVP;
		DWORD iAttributeSW;
	};
	class CAnimation;
	/*!
	 *@brief	スキンモデルデータ
	 */
	class CSkinModelData{
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
		 * @brief	モデルデータをロード。
		 *@param[in]	filePath	ファイルパス。
		 *@param[out]	anim		アニメーション付きモデルデータの場合、アニメーションクラスも構築されます。
		 */
		void LoadModelData( const char* filePath, CAnimation* anim );
		/*!
		* @brief	リリース。
		*/
		void Release();
		LPD3DXFRAME GetFrameRoot()
		{
			return m_frameRoot;
		}
		ID3DXAnimationController* GetAnimationController()
		{
			return m_pAnimController;
		}
		/*!
		* @brief	ボーン行列を更新。
		*/
		void UpdateBoneMatrix( const CMatrix& matWorld );
	private:
		LPD3DXFRAME					m_frameRoot;		//フレームルート。
		ID3DXAnimationController*   m_pAnimController;	//アニメーションコントローラ。
	};
}

#endif //_TKSKINMODELDATA_H_
