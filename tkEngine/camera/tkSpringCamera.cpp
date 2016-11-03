/*!
 * @brief	バネカメラ。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/camera/tkSpringCamera.h"

namespace tkEngine{
	namespace {
		float dampingK = 35.0f;
		float dampingRate = 1.0f;
		/*!
		* @brief	バネ減衰を使用して、現在の位置、目標となる位置、速度、加速度から新しい位置を計算する。
		*/
		CVector3 CalcSpring( 
			const CVector3& positionNow, 
			const CVector3& positionTarget, 
			CVector3& moveSpeed ,
			float maxMoveSpeed
		)
		{
			//現在の位置と目標の位置との差分を求める。
			CVector3 distance;
			distance.Subtract( positionTarget, positionNow );
			
			CVector3 springAccel;
			springAccel = distance;
			
			float t = dampingK / (2.0f * dampingRate);
			float springK = t * t;
			springAccel.Scale(springK);
			//加速度を決定。
			CVector3 vt = moveSpeed;
			vt.Scale(dampingK);
			springAccel.Subtract(vt);
			
			springAccel.Scale(GameTime().GetFrameDeltaTime());
			moveSpeed.Add(springAccel);
			if (moveSpeed.LengthSq() > maxMoveSpeed*maxMoveSpeed) {
				//最高速度より速くなってしまった。
				moveSpeed.Normalize();
				moveSpeed.Scale(maxMoveSpeed);
			}
			CVector3 newPos = positionNow;
			CVector3 addPos = moveSpeed;
			addPos.Scale(GameTime().GetFrameDeltaTime());
			if (moveSpeed.LengthSq() > maxMoveSpeed*maxMoveSpeed) {
				//最高速度より速くなってしまった。
				moveSpeed.Normalize();
				moveSpeed.Scale(maxMoveSpeed);
			}
			newPos.Add(addPos);
			return newPos;
		}
	}
	/*!
	 * @brief	コンストラクタ。
	 */
	CSpringCamera::CSpringCamera()
	{
	}
	/*!
	 * @brief	デストラクタ
	 */
	CSpringCamera::~CSpringCamera()
	{
	}
	/*!
	* @brief	初期化。
	*/
	void CSpringCamera::Init(const CVector3& target, const CVector3& position, float maxMoveSpeed)
	{
		m_camera.SetTarget(target);
		m_camera.SetPosition(position);
		m_target = target;
		m_position = position;
		m_targetMoveSpeed = CVector3::Zero;
		m_positionMoveSpeed = CVector3::Zero;
		m_maxMoveSpeed = maxMoveSpeed;
	}
	/*!
	 * @brief	更新。
	 */
	void CSpringCamera::Update()
	{
		CVector3 target = CalcSpring(m_camera.GetTarget(), m_target, m_targetMoveSpeed, m_maxMoveSpeed);
		CVector3 position = CalcSpring(m_camera.GetPosition(), m_position,  m_positionMoveSpeed, m_maxMoveSpeed);
		m_camera.SetTarget(target);
		m_camera.SetPosition(position);
		m_camera.Update();
	}
}