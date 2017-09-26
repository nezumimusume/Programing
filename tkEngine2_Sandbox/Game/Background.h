#pragma once

#include "tkEngine/physics/tkMeshCollider.h"
#include "tkEngine/physics/tkRigidBody.h"

class Background : public IGameObject
{
public:
	Background();
	~Background();
	bool Start() override;
	void Update() override;
	void Render(CRenderContext& rc) override;
private:
	CSkinModelData		m_skinModelData;	//!<スキンモデルデータ。
	CSkinModel			m_skinModel;		//!<スキンモデル。
	CSkinModelData		m_skinModelData2;
	CSkinModel			m_skinModel2;
	CShaderResourceView	m_normalMapSRV;		//!<法線マップのSRV。
	CMeshCollider		m_meshCollider;		//!<メッシュコライダー。
	CRigidBody			m_rigidBody;		//!<剛体。
	CMeshCollider		m_meshCollider2;	//!<メッシュコライダー２。
	CRigidBody			m_rigidBody2;		//!<剛体２。
};

