#include "pch.h"
#include "CStar.h"
#include "CScrollManager.h"
#include "CBitmapManager.h"

CStar::CStar()
{
    m_eItemType = ITEM_STAR;
}

CStar::~CStar()
{
}

void CStar::Initialize()
{
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
	m_fSpeed = 5.f;
	m_bIsGround = false;
	m_tDir = { 1 , 1 };
}

int CStar::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;

	if (m_fTime >= 30) {
		m_tDir.SetX(m_tDir.GetX() * -1);
		m_fTime = 0.f;
	}

	m_tInfo.fX += m_tDir.GetX() * m_fSpeed;
	m_tInfo.fY += m_tDir.GetY() * m_fSpeed;
	m_fTime += 0.2f;
	__super::UpdateRect();

	return OBJ_NOEVENT;
}

void CStar::LateUpdate()
{
	if (!m_bIsGround && m_fTime >= 2.f) m_tDir.SetY(1);
}

void CStar::OnCollision(CObject* _op)
{
	if (OBJ_PLAYER == _op->GetOBJID()) {
		SetIsDead(true);
	}

	if (OBJ_BLOCK == _op->GetOBJID()) {
		m_tDir.SetY(-1);
		m_bIsGround = false;
		m_fTime = 0.f;
	}
}
