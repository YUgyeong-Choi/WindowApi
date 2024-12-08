#include "pch.h"
#include "CProjectile.h"
#include "CScrollManager.h"

CProjectile::CProjectile()
{
}

void CProjectile::Initialize()
{
	m_tInfo = { WINCX / 2, WINCY / 2, 20.f, 20.f };
	m_fSpeed = 10.f;
}

int CProjectile::Update()
{
	if (m_bIsDead && !m_bIsActive) return OBJ_DEAD;
	if (m_fAngle == 180.f) m_tInfo.fX -= m_fSpeed;
	else m_tInfo.fX += m_fSpeed;
	
	__super::UpdateRect();
	return OBJ_NOEVENT;
}

void CProjectile::LateUpdate()
{
	if (!CheckBoundary())
	{
		m_bIsDead = true;
		m_bIsActive = false;
	}
}

void CProjectile::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect, {0.f, 0.f}, 0.f, 0.f, RGB(255, 0, 0));
}

void CProjectile::Release()
{
}

void CProjectile::OnCollision(CObject* _op)
{
}

void CProjectile::OnDead()
{
}

bool CProjectile::CheckBoundary()
{
	if (m_tInfo.fX > WINCX) return false;
	else if (m_tInfo.fX < 0) return false;
	return true;
}

void CProjectile::Jump()
{
}
