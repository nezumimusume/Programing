/*!
 * @brief	空。
 */
#pragma once
#include "tkEngine/resource/tkSkinModelDataHandle.h"
#include "tkEngine/graphics/tkSkinModel.h"
#include "tkEngine/graphics/tkAtmosphericScatteringParam.h"
#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/gameObject/tkGameObject.h"

namespace tkEngine{
	/*!
	 * @brief	空のシミュレーションクラス。
	 * @details
	 *  tkEngine::Sky().SetEnableをコールすることで空のシミュレーションが行えるようになります。</br>
	 *  SetEnable関数の詳細については関数の説明を参照して下さい。</br>
	 *  空は大きな球体のモデルがカメラの注視点を中心として描画されます。</br>
	 *  空に貼られているテクスチャはAssets/modelData/sky.ddsです。</br>
	 *  空のテクスチャを変更したい場合はこのテクスチャを上書きしてください。</br>
	 *  テクスチャは空に投影するキューブマップになっている必要があるので注意してください。</br>
	 *  また、このシミュレーションで行われている処理では空の色はテクスチャからサンプリングしているのではなく、</br>
     *  大気錯乱の計算が行われて決定されます。テクスチャは雲の形状をレンダリングするためだけに使用されているので注意してください。</br>
     * @todo
     *  未実装の機能として、雲の形状を抽出するための閾値が決め打ちになっているため、異なるテクスチャを</br>
     *  使用した場合に雲が綺麗に表示されないことが想定されます。</br>
     *  問題が起きた場合はその閾値を調整できるようにする必要があります。</br>
     *@code
     		void Init()
     		{
				//空のシミュレーションを有効にする。
				Sky().SetEnable( &camera, &light );
			}
     *@endcode
	 */
	class CSky : public IGameObject {
		enum InitStep {
			InitStep_Load,
			InitStep_Wait,
		};
		CSkinModelDataHandle	skinModelData;					//!<スキンモデルデータ。
		CSkinModel				skinModel;						//!<スキンモデル。
		CAnimation				animation;						//!<アニメーション。
		CLight					light;							//!<ライト。
		CTexture				normalMap;
		InitStep				initStep = InitStep_Load;
		SAtmosphericScatteringParam	atomosphereParam;			//!<大気錯乱パラメータ。
		CVector3				sunPosition = CVector3::Zero;	//!<太陽の位置。
		float					sunAngle = 0.0f;
		CLight					sunLight;						//!<ライト。
		CSkinModelDataHandle	sunModelData;					//!<太陽のモデルデータ。
		CSkinModel				sunModel;						//!<太陽のモデル。
		CVector3				sunDir = CVector3::Zero;		//!<太陽の方向。
		float					deltaTimeMul = 1.0f;			//!<⊿タイムに乗算される値。
		const CCamera*			camera = nullptr;				//!<カメラ。
		CLight*					sceneLight = nullptr;								//!<シーンライト。
		CVector3				dayAmbinetLight = CVector3(0.3f, 0.3f, 0.3f);		//!<日中のアンビエントライト。
		CVector3				nightAmbinetLight = CVector3(0.1f, 0.1f, 0.1f);		//!<夜間のアンビエントライト。
	public:
		CSky();
		
		~CSky()
		{

		}
		bool Start() override;
		
		void Update() override;
		/*!
		 *@brief	空のシミュレーションを有効にする。
		 *@details
		 *  空のシミュレーションが有効になります。空をレンダリングするためにカメラは必ず設定してください。</br>
		 *  ライトを設定すると、太陽の動きに合わせたライトの計算が行われます。</br>
		 *  ディフューズライトの一本目、リムライト、アンビエントライトが計算されるようになります。</br>
		 *  ゲーム側で上記のライトの値を変更することは可能ですが、シミュレーションの結果に変化が起きるので注意してください。</br>
		 *@param[in]	camera		シーンカメラ。
		 *@param[in]	light		ライト(NULLの指定も可能。)
		 */
		void SetEnable( const CCamera* camera, CLight* light )
		{
			this->camera = camera;
			sceneLight = light;
			SetActiveFlag(true);
		}
		/*!
		 * @brief	空のシミュレーションを無効にする。
		 */
		void SetDisable()
		{
			SetActiveFlag(false);
		}
		/*!
		* @brief	太陽の明るさを設定。
		*/
		void SetLuminance(const CVector3& luminance)
		{
			sunLight.SetEmissionLightColor(luminance);
		}
		/*!
		 * @brief	カメラを設定。
		 */
		void SetCamera( const CCamera& camera )
		{
			this->camera = &camera;
		}
		/*!
		 * @brief	ゲームシーンで使用しているライトを設定。
		 *@details
		 * このライトを設定するとディフューズライトの一本目とリムライト、アンビエントライトが
		 * 太陽の動きから計算されるようになります。
		 * ゲーム側で上記のライトの値を変更することはできますが、
		 * 大気シミュレーションに変化が起きるので注意してください。
		 *@param[in]	light		ライト。
		 */
		void SetSceneLight( CLight& light )
		{
			sceneLight = &light;
		}
		/*!
		 * @brief	日中のアンビエントライトを設定。
		 */
		void SetDayAmbientLight( const CVector3& lig )
		{
			dayAmbinetLight = lig;
		}
		/*!
		 * @brief	夜間のアンビエントライトを設定。
		 */
		void SetNightAmbientLight( const CVector3& lig )
		{
			nightAmbinetLight = lig;
		}
		//大気錯乱パラメーターを取得。
		const SAtmosphericScatteringParam& GetAtomosphereParam() const
		{
			return atomosphereParam;
		}
		void Render(CRenderContext& renderContext) override;
		/*!
		 * @brief	太陽の位置を設定。
		 */
		void SetSunPosition( const CVector3& position )
		{
			sunPosition = position;
		}
		/*!
		* @brief	太陽の座標を取得。
		*/
		const CVector3& GetSunPosition() const
		{
			return sunPosition;
		}
		/*!
		* @brief	太陽の方向を取得。
		* @details
		*  惑星の中心から見た場合の太陽の方向です。
		*/
		const CVector3& GetSunDir() const
		{
			return sunDir;
		}
		/*!
		* @brief	⊿タイムに乗算される値を設定。
		*@param[in]	mul		グローバル⊿タイムに乗算される値。この値に0.5を設定するとエネミーの挙動が0.5倍速になります。
		*/
		void SetFrameDeltaTimeMul(float mul)
		{
			deltaTimeMul = mul;
		}
		void Init();
	};
}
