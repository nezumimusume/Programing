/*!
 *@brief	地形。
 */

#pragma once

#include "tkEngine/Physics/tkMeshCollider.h"
#include "tkEngine/Physics/tkRigidBody.h"

namespace tkEngine{
	/*!
	 *@brief	地形。
	 *@detail
	 * スプラットマップを使用した地形処理。登録できるテクスチャの数は４枚(増やすことは可能。)</br>
	 * スプラットマップのR成分は0番目のテクスチャ、G成分は１番目のテクスチャ、B成分は2番目のテクスチャ</br>
	 * α成分は3番目のテクスチャの重みになる。</br>
	 * 例えば、スプラットマップのテクセルがRGBA(255,255,0,0)の場合は、</br>
	 * 0番目のテクスチャ×0.5＋1番目のテクスチャ×0.5となる。</br>
	 */
	class CTerrain : public IGameObject {
	public:
		/*!
		 *@brief	コンストラクタ。
		 */
		CTerrain();
		/*!
		 *@brief	デストラクタ。
		 */
		~CTerrain();
		/*!
		 *@brief	初期化。
		 *@param[in]	skinModelDataPath	スキンモデルデータのパス。
		 *@param[in]	splatMapPath		スプラットマップのパス。
		 *@param[in]	texturePaths		地形のテクスチャのパス。最大MAX_TEXTUREの数だけ指定できる。終端にはNULLを指定してください。
		 *@param[in]	camera				カメラ。
		 *@param[in]	light				ライト。
		 */
		void Init( 
			const char* skinModelDataPath, 
			const char* splatMapPath, 
			const char* texturePaths[],
			const CCamera& camera,
			const CLight& light
		);
		bool Start() override;
		void Update() override;
		void Render(CRenderContext& renderContext) override;
		/*!
		 *@brief	座標を設定する。
		 *@param[in]	pos		座標。
		 */
		void SetPosition(const CVector3& pos)
		{
			m_position = pos;
		}
		/*!
		 *@brief	回転を設定する。
		 *@param[in]	rot		回転。
		 */
		void SetRotation(const CQuaternion& rot)
		{
			m_rotation = rot;
		}
		/*!
		 *@brief	拡大率を設定。
		 */
		void SetScale(const CVector3& scale)
		{
			m_scale = scale;
		}
	private:
		/*!
		*@brief	地形の幅と高さを計算。
		*/
		void CalcWidthAndHeight();
	private:
		/*!
		 *@brief	初期化ステップ。
		 */
		enum class InitStep{
			enStartLoad,	//!<ロード開始。
			enWatiLoad,		//!<ロード待機。
		};
		
		static const int MAX_TEXTURE = 4;							//!<地形のテクスチャの最大数。
		CSkinModelDataHandle	m_skinModelData;					//!<スキンモデルデータ。
		InitStep				m_initStep = InitStep::enStartLoad;	//!<ロード開始ステップ。
		CSkinModel				m_skinModel;						//!<スキンモデル。
		const CLight*			m_light = nullptr;					//!<ライト。
		CTexture				m_splatMap;							//!<スプラットマップ。
		CTexture				m_textures[MAX_TEXTURE];			//!<地形テクスチャ。
		CVector3				m_position = CVector3::Zero;		//!<座標。
		CQuaternion				m_rotation = CQuaternion::Identity;	//!<回転。
		CVector3				m_scale = CVector3::One;			//!<拡大。
		std::string				m_skinModelDataPath;				//!<スキンモデルデータパス。
		std::string				m_splatMapPath;						//!<スプラットマップのパス。
		std::string				m_texturePaths[MAX_TEXTURE];		//!<地形のテクスチャのパス。
		const CCamera*			m_camera = nullptr;					//!<カメラ。
		CMeshCollider			m_meshCollider;						//!<メッシュコライダー。
		CRigidBody				m_rigidBody;						//!<剛体。
		CVector4				m_terrainSize = {0.0f, 0.0f, 0.0f, 0.0f};	//!<地形のサイズ。
	};
}