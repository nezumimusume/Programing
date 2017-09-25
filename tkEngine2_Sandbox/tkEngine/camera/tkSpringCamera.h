/*!
 * @brief	バネカメラ
 */

#pragma once

#include "tkEngine/graphics/tkCamera.h"
#include "tkEngine/camera/tkCameraCollisionSolver.h"

namespace tkEngine{
	/*!
	 * @brief	バネカメラ。
	 * @details
	 *  バネに引っ張られるようなカメラの挙動を実現するクラスです。</br>
	 *  SetTarTarget関数とSetTarPosition関数を使用して</br>
	 *  カメラの目標となる注視点と視点を設定してください。</br>
	 *  Update関数を実行することで、カメラが設定された目標座標に追従していきます。</br>
	 * @code
	 *		CSpringCamera springCamera;
			//初期化。
	 		void Init()
	 		{
				springCamera.Init(
					CVector3(0.0f, 0.0f, 0.0f),			
					CVector3(0.0f, 0.0f, 100.0f), 
					100.0f
				);
	 		}
			//更新。
			void Update()
			{
					・
					・
					・
				//カメラの注視点を設定する。
				springCamera.SetTarTarget(target);
				springCamera.SetTarPosition(position);

				//カメラを動かす。
				springCamera.Update();
			}
	 * @endcode 
	 */
	class CSpringCamera{
	public:
		/*!
		 * @brief	コンストラクタ。
		 */
		CSpringCamera();
		/*!
		 * @brief	デストラクタ
		 */
		~CSpringCamera();
		/*!
		* @brief	初期化。
		*@param[in]	camera			カメラ。
		*@param[in]	maxMoveSpeed	カメラの最大移動速度。
		*@param[in] isEnableCollisionSolver	コリジョン処理を有効にする？
		*@param[in]	sphereCollisionRadius	球体コリジョンの半径。isEnableCollisionSoloverがtrueの時に有効になります。
		*/
		void Init(
			CCamera* camera,
			float maxMoveSpeed,
			bool isEnableCollisionSolver,
			float sphereCollisionRadius
		);
		/*!
		 * @brief	目標となる注視点を設定。
		 */
		void SetTarTarget( const CVector3& target )
		{
			m_target = target;
		}
		/*!
		 * @brief	目標となる視点を設定。
		 */
		void SetTarPosition( const CVector3 position )
		{
			m_position = position ;
		}
		/*!
		* @brief	注視点を設定。
		*/
		void SetTarget(const CVector3& target)
		{
			if (m_camera == nullptr) {
				return;
			}
			m_camera->SetTarget(target);
		}
		/*!
		* @brief	視点を設定。
		*/
		void SetPosition(const CVector3 position)
		{
			if (m_camera == nullptr) {
				return;
			}
			m_camera->SetPosition(position);
		}
		/*!
		* @brief	遠平面を設定。
		*/
		void SetFar(float _far)
		{
			if (m_camera == nullptr) {
				return ;
			}
			m_camera->SetFar(_far);
		}
		/*!
		* @brief	近平面を設定。
		*/
		void SetNear(float _near)
		{
			if (m_camera == nullptr) {
				return;
			}
			m_camera->SetNear(_near);
		}
		/*!
		* @brief	カメラの回転行列を取得。
		*/
		const CMatrix& GetCameraRotation() const
		{
			if (m_camera == nullptr) {
				return CMatrix::Identity;
			}
			return m_camera->GetCameraRotation();
		}
		/*!
		* @brief	注視点を取得。
		*/
		const CVector3& GetTarget() const
		{
			if (m_camera == nullptr) {
				return CVector3::Zero;
			}
			return m_camera->GetTarget();

		}
		/*!
		* @brief	視点を取得。
		*/
		const CVector3& GetPosition() const
		{
			if (m_camera == nullptr) {
				return CVector3::Zero;
			}
			return m_camera->GetPosition();
		}
		
		/*!
		 * @brief	更新。
		 */
		void Update();
		/*!
		 * @brief	カメラを取得。
		 */
		const CCamera* GetCamera() const
		{
			return m_camera;
		}
		/*!
		* @brief	バネの減衰率を設定。
		*@detail
		* 値が大きいほどカメラが遅れて付いてきます。
		*/
		void SetDampingRate(float dampingRate)
		{
			m_targetDampingRate = dampingRate;
		}
		/*!
		* @brief	カメラを取得。
		*/
		CCamera* GetCamera() 
		{
			return m_camera;
		}
		void SetViewAngle(float angle)
		{
			if (m_camera == nullptr) {
				return;
			}
			m_camera->SetViewAngle(angle);
		}
		float GetViewAngle() const
		{
			if (m_camera == nullptr) {
				return 0.0f;
			}
			return m_camera->GetViewAngle();
		}

		/*!
		* @brief	目標となる注視点を取得。
		*/
		const CVector3& GetTarTarget() const
		{
			return m_target;
		}
		/*!
		* @brief	目標となる視点を取得。
		*/
		const CVector3& GetTarPosition() const
		{
			return m_position;
		}
		/*!
		* @brief	バネカメラ用のパラメータをクリア。
		*/
		void ClearSpringParame()
		{
			m_targetMoveSpeed = CVector3::Zero;
			m_positionMoveSpeed = CVector3::Zero;

		}
		/*!
		* @brief	バネカメラの更新処理。
		* @details
		*  Update関数から呼ばれています。</br>
		*  バネカメラの更新処理だけ個別で呼びたいなどの特殊なケースで使用してください。</br>
		*/
		void UpdateSpringCamera();
		/*!
		* @brief	カメラの更新。
		* @details
		*  Update関数から呼ばれています。</br>
		*  カメラの更新処理だけ個別で呼びたいなどの特殊なケースで使用してください。</br>
		*/
		void UpdateCamera()
		{
			if (m_camera) {
				m_camera->Update();
			}
		}
	private:
		CCamera*	m_camera = nullptr;				//!<カメラ。
		CVector3	m_target = CVector3::Zero;		//!<目標となる注視点。
		CVector3	m_position = CVector3::Zero;	//!<目標となる視点。
		CVector3	m_targetMoveSpeed = CVector3::Zero;		//!<注視点の移動速度。
		CVector3	m_positionMoveSpeed = CVector3::Zero;	//!<視点の移動速度。
		float		m_maxMoveSpeed = 0.0f;					//!<最高移動速度。
		float		m_targetDampingRate = 1.0f;				//!<減衰率。値が大きいほどカメラが遅れ付いてくる。
		float		m_dampingRate = 1.0f;					//!<減衰率。
		float		m_dampingRateVel = 0.0f;
		bool		m_isEnableCollisionSolver = false;		//!<コリジョン処理が有効？
		CCameraCollisionSolver m_cameraCollisionSolver;
	};
}