#include "pch.h"
#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
	Release();
}

void Bullet::Initialize()
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;
	m_fSpeed = 10.f;
}

int Bullet::Update()
{
	if (m_bDead) {
		return OBJ_DEAD;
	}
	m_tInfo.fX = long(m_tInfo.fX + (m_fSpeed * cosf(m_fAngle * (PI / 180.f))));
	m_tInfo.fY = long(m_tInfo.fY + (m_fSpeed * sinf(m_fAngle * (PI / 180.f))));

	Obj::Update_Rect();
	return OBJ_NOEVENT;
}

void Bullet::Late_Update()
{
	if (m_tRect.left <= GAME_WIN_LEFT || m_tRect.top <= GAME_WIN_TOP || m_tRect.right >= GAME_WIN_RIGHT || m_tRect.bottom >= GAME_WIN_BOTTOM) {
		m_bDead = true;
	}
}

void Bullet::Render(HDC _hdc)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(220, 20, 60));
	HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, myBrush);
	Ellipse(_hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(_hdc, oldBrush);
	DeleteObject(myBrush);
}

void Bullet::Release()
{
}
