#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}


bool Player::Start()
{
	m_skinModelData.Load(L"modelData/Thethief_H.cmo");
	m_skinModel.Init(m_skinModelData);
	return true;
}

void Player::Update()
{
	m_skinModel.Update(CVector3::Zero, C
}

void Player::Render(CRenderContext& rc)
{
}