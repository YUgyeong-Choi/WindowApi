#include "pch.h"
#include "CFlower.h"
#include "CScrollManager.h"
#include "CPlayerDH.h"
#include "CBitmapManager.h"

CFlower::CFlower():m_iAiDir(0)
{
	m_eItemType = ITEM_FLOWER;
}

CFlower::~CFlower()
{
}
void CFlower::Initialize()
{
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
	m_fSpeed = 5.f;
	m_bIsGround = false;
	m_tDir = { 0 , 1 };
	m_iAiDir = 1;
}

int CFlower::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;

	if (m_fTime >= 20) {
		m_tDir.SetX(m_iAiDir);
		m_iAiDir *= -1;
		m_fTime = 0.f;
	}

	m_tInfo.fX += m_tDir.GetX() * m_fSpeed;
	m_tInfo.fY += m_tDir.GetY() * m_fSpeed;
	m_fTime += 0.2f;
	__super::UpdateRect();

	return OBJ_NOEVENT;
}

void CFlower::LateUpdate()
{
	if (!m_bIsGround && m_fTime >= 2.f) m_tDir.SetY(1);
}



void CFlower::OnCollision(CObject* _op)
{
	if (OBJ_PLAYER == _op->GetOBJID()) {
		SetIsDead(true);
	}

	if (_op->GetOBJID() == OBJ_BLOCK) {
		m_tDir.SetX(m_tDir.GetX() * -1);
	}
}
