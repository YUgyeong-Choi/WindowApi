#include "pch.h"
#include "CItem.h"
#include "CScrollManager.h"

CItem::CItem()
{
}

void CItem::Initialize()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;
	m_fSpeed = -3.f;
	m_fJumpPower = 20.f;
	m_bActionStatus = AS_FALL;
	m_fFallSpeed = 5.f;
}

int CItem::Update()
{
	if (m_bActionStatus == AS_FALL) {
		m_tInfo.fY += m_fFallSpeed;
	}

	if (m_bIsDead) {
		return OBJ_DEAD;
	}

	if (m_bActionStatus == AS_STOP) {
		m_tInfo.fX += m_fSpeed;
		if (m_tInfo.fX > 300 || m_tInfo.fX < 100) {
			m_fSpeed *= -1;
		}
		SetActionStatus(AS_FALL);
	}

	__super::UpdateRect();
	return OBJ_NOEVENT;
}

void CItem::LateUpdate()
{
}

void CItem::Render(HDC hDC)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(200, 103, 163));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Rectangle(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
	if (g_bDevmode) Hitbox(hDC, m_tRect);
}

void CItem::Release()
{
}

void CItem::OnCollision(CObject* _op)
{
}

void CItem::OnDead()
{
}
