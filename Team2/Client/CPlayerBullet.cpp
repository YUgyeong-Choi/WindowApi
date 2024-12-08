#include "pch.h"
#include "CPlayerBullet.h"
#include "CScrollManager.h"

CPlayerBullet::CPlayerBullet()
{
}

void CPlayerBullet::Initialize()
{
	m_tInfo.fCX = 15.f;
	m_tInfo.fCY = 15.f;
	m_fSpeed = 5.f;
	m_fJumpPower = 10.f;
}

int CPlayerBullet::Update()
{
	if (true == m_bIsDead)
		return OBJ_DEAD;

	m_tInfo.fX += m_fJumpPower * cosf(m_fAngle) * m_fTime; // 플레이어 방향에따라서 쏨
	m_tInfo.fY -= (m_fJumpPower * sinf(45.f) * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.5f;
	m_fTime += 0.1f;

	CObject::UpdateRect();

	return OBJ_NOEVENT;
}

void CPlayerBullet::LateUpdate()
{
}

void CPlayerBullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
}

void CPlayerBullet::Release()
{
}

void CPlayerBullet::OnCollision(CObject* _op)
{
}

void CPlayerBullet::OnDead()
{
}
