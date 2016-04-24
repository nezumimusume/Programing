#include "stdafx.h"
#include "Player.h"
#include "tkEngine/graphics/tkCamera.h"
#include "bulletPhysics.h"

struct SweepResultGround : public btCollisionWorld::ConvexResultCallback
{
	bool isHit;
	CVector3 hitPos;
	
	SweepResultGround()
	{
		isHit = false;
	}

	virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject->getUserIndex() != -1) {
			//無視。
			return 0.0f;
		}
		CVector3 hitPointNormal;
		hitPointNormal.Set(
			convexResult.m_hitNormalLocal.x(), 
			convexResult.m_hitNormalLocal.y(), 
			convexResult.m_hitNormalLocal.z()
			);
		float d = hitPointNormal.Dot(CVector3::Up);
		if (d < 0.0f) {
			//当たってない。
			return 0.0f;
		}
		if (acosf(d) > CMath::PI * 0.2) {
			//ホントは地面かどうかとかの属性を見るのがベストなんだけど、今回は角度で。
			return 0.0f;
		}
		isHit = true;
		hitPos.Set( 
			convexResult.m_hitPointLocal.x(), 
			convexResult.m_hitPointLocal.y(), 
			convexResult.m_hitPointLocal.z() );
		return 0.0f;
	}
};
struct SweepResultWall : public btCollisionWorld::ConvexResultCallback
{
	CVector3 hitNormalXZ;
	bool isHit;
	CVector3 hitPos;
	SweepResultWall()
	{
		isHit = false;
	}
	
	virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject->getUserIndex() != -1) {
			//無視。
			return 0.0f;
		}
		CVector3 hitPointNormal;
		hitPointNormal.Set(
			convexResult.m_hitNormalLocal.x(),
			convexResult.m_hitNormalLocal.y(),
			convexResult.m_hitNormalLocal.z()
			);
		float d = hitPointNormal.Dot(CVector3::Up);
		if (acosf(d) < CMath::PI * 0.2) {
			//ホントは地面かどうかとかの属性を見るのがベストなんだけど、今回は角度で。
			return 0.0f;
		}
		isHit = true;
		//XZ平面での法線。
		hitNormalXZ.x = hitPointNormal.x;
		hitNormalXZ.y = 0.0f;
		hitNormalXZ.z = hitPointNormal.z;
		hitNormalXZ.Normalize();

		btTransform transform = convexResult.m_hitCollisionObject->getWorldTransform();
		hitPos.Set(
			convexResult.m_hitPointLocal.x(),
			convexResult.m_hitPointLocal.y(),
			convexResult.m_hitPointLocal.z());
		return 0.0f;
	}
};
void CPlayer::Start()
{
	m_radius = 0.05f;
	m_shape.Create(m_radius, 10, 0xffff0000, true);
	m_position = CVector3::Zero;
	m_position.y = m_radius * 10.0f;
	m_light.SetAmbinetLight(CVector3(0.5f, 0.5f, 0.5f));
	m_light.SetDiffuseLightColor(0, CVector4(0.5f, 0.5f, 0.5f, 1.0f));
	m_light.SetDiffuseLightDirection(0, CVector3(1.0f, 0.0f, 0.0f));
	m_shadowModel.Create(m_shape.GetPrimitive());
	
	//コリジョン初期化。
	m_collisionShape = new btSphereShape(m_radius);
	float mass = 1000.0f;
	btTransform rbTransform;
	rbTransform.setIdentity();
	rbTransform.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));
	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	m_myMotionState = new btDefaultMotionState(rbTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_collisionShape, btVector3(0, 0, 0));
	m_rigidBody = new btRigidBody(rbInfo);
	m_rigidBody->setUserIndex(0);
	//ワールドに追加。
	g_bulletPhysics.AddRigidBody(m_rigidBody);
}
void CPlayer::PreUpdate()
{
	static float deltaTime = 1.0f / 60.0f;
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	if (KeyInput().IsUpPress())
	{
		m_moveSpeed.z += 0.6f;
	}
	if (KeyInput().IsDownPress())
	{
		m_moveSpeed.z -= 0.6f;
	}
	if (KeyInput().IsRightPress())
	{
		m_moveSpeed.x += 0.6f;
	}
	if (KeyInput().IsLeftPress())
	{
		m_moveSpeed.x -= 0.6f;
	}

	if (KeyInput().IsTrggerA()) {
		m_moveSpeed.y = 2.2f;
	}
	static CVector3 gravity(0.0f, -9.8f, 0.0f);
	CVector3 addGravity = gravity;
	addGravity.Scale(deltaTime);
	m_moveSpeed.Add(addGravity);
	CVector3 addPos;
	addPos = m_moveSpeed;
	addPos.Scale(deltaTime);

	//XZ平面を調べる。
	{
		int loopCount = 0;
		while (true) {
			btTransform start, end;
			start.setIdentity();
			end.setIdentity();
			start.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));
			CVector3 newPos;
			SweepResultWall callback;
			CVector3 addPosXZ = addPos;
			addPosXZ.y = 0.0f;
			if (addPosXZ.Length() > 0.0001f) {
				newPos.Add(m_position, addPosXZ);
				end.setOrigin(btVector3(newPos.x, newPos.y, newPos.z));

				g_bulletPhysics.ConvexSweepTest(m_collisionShape, start, end, callback);
			}
			if (callback.isHit) {
				//当たった。
				//壁。
				addPos.x = callback.hitPos.x - m_position.x;
				addPos.z = callback.hitPos.z - m_position.z;

				CVector3 t;
				t.x = -addPos.x;
				t.y = 0.0f;
				t.z = -addPos.z;
				t.Normalize();
				//半径分押し戻す。
				t.Scale(m_radius);
				addPos.Add(t);
				//続いて壁に沿って滑らせる。
				//滑らせる方向を計算。
				t.Cross(callback.hitNormalXZ, CVector3::Up);
				t.Normalize();
				t.Scale(t.Dot(addPosXZ));
				addPos.Add(t);	//滑らせるベクトルを加算。
			}
			else {
				//どことも当たらないので終わり。
				break;
			}
			loopCount++;
			if (loopCount == 5) {
				break;
			}
		}
	}
	//下方向を調べる。
	{
		btTransform start, end;
		start.setIdentity();
		end.setIdentity();
		start.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));
		CVector3 newPos;
		SweepResultGround callback;
		if (fabsf(addPos.y) > 0.0001f) {
			newPos = m_position;
			newPos.y += addPos.y;

			end.setOrigin(btVector3(newPos.x, newPos.y, newPos.z));

			g_bulletPhysics.ConvexSweepTest(m_collisionShape, start, end, callback);
		}
		if (callback.isHit) {
			//当たった。
			//地面。
			m_moveSpeed.y = 0.0f;
			addPos.y = callback.hitPos.y - m_position.y;
			addPos.y += m_radius;
		}
	}
	m_position.Add(addPos);
	
	const btVector3& rPos = m_rigidBody->getWorldTransform().getOrigin();
	
	m_rigidBody->getWorldTransform().setOrigin(btVector3(m_position.x, m_position.y, m_position.z));
}
void CPlayer::Update()
{
	m_shape.SetPosition(m_position);
	m_shape.UpdateWorldMatrix();
	m_shadowModel.SetWorldMatrix(m_shape.GetWorldMatrix());
	ShadowMap().Entry(&m_shadowModel);
}
void CPlayer::Render(CRenderContext& renderContext)
{
	m_shape.RenderLight(
		renderContext,
		m_camera->GetViewProjectionMatrix(),
		m_light,
		false,
		false
	);
}