#include "pch.h"
#include "Shield.h"

Shield::Shield()
{
}

Shield::~Shield()
{
	Release();
}

void Shield::Initialize()
{
	m_tInfo.fCX = 15.f;
	m_tInfo.fCY = 15.f;
	m_fDistance = 70.f;
	m_fSpeed = 5.f;

	m_iHp = 1;
	m_iDamage = 100;
}

int Shield::Update()
{
	if (m_bDead) {
		return OBJ_DEAD;
	}
	m_fAngle += m_fSpeed;
	m_tInfo.fX = m_pTarget->Get_Info().fX + (m_fDistance * cosf(m_fAngle * (PI / 180.f)));
	m_tInfo.fY = m_pTarget->Get_Info().fY - (m_fDistance * sinf(m_fAngle * (PI / 180.f)));

	Obj::Update_Rect();
	return OBJ_NOEVENT;
}

void Shield::Late_Update()
{
	if (m_iHp <= 0) {
		m_bDead = true;
	}
}

void Shield::Render(HDC _hdc)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 192, 203));
	HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, myBrush);
	Ellipse(_hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(_hdc, oldBrush);
	DeleteObject(myBrush);
}

void Shield::Release()
{
}