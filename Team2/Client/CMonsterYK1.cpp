#include "pch.h"
#include "CMonsterYK1.h"
#include "CScrollManager.h"

void CMonsterYK1::Initialize()
{
	m_tInfo = { 1000, 400, 40, 40 };
	m_fSpeed = 3.f;
	m_tDir = { -1 , 1 };
	m_bIsGround = false;
}

int CMonsterYK1::Update()
{
	if (m_bIsDead) return OBJ_DEAD;
	if (FindPlayer()) {
		m_tInfo.fX += m_tDir.GetX() * m_fSpeed;
		m_tInfo.fY += m_tDir.GetY() * m_fSpeed;
	}
	__super::UpdateRect();
	return 0;
}

void CMonsterYK1::LateUpdate()
{
}

void CMonsterYK1::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
	if (g_bDevmode) Hitbox(hDC, m_tRect);
}

void CMonsterYK1::Release()
{
}

void CMonsterYK1::OnCollision(CObject* _op)
{
	if (_op->GetOBJID() == OBJ_PLAYER) {
		SetIsDead(true);
	}
}

void CMonsterYK1::OnDead()
{
}
