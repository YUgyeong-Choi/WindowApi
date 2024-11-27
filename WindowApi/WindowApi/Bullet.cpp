#include "Bullet.h"

Bullet::Bullet():m_dir(DIR::NONE)
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

	switch (m_dir)
	{
	case LEFT:
		m_tInfo.fX -= m_fSpeed;
		break;
	case UP:
		m_tInfo.fY -= m_fSpeed;
		break;
	case RIGHT:
		m_tInfo.fX += m_fSpeed;
		break;
	case DOWN:
		m_tInfo.fY += m_fSpeed;
		break;
	default:
		break;
	}

	Obj::Update_Rect();
	return OBJ_NOEVENT;
}

void Bullet::LateUpdate()
{
	if (m_tRect.left <= 100 || m_tRect.top <= 100 || m_tRect.right >= WINCX - 100 || m_tRect.bottom >= WINCY - 100) {
		m_bDead = true;
	}
}

void Bullet::Render(HDC _hdc)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(220, 20, 60));
	HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, myBrush); 
	Rectangle(_hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(_hdc, oldBrush);
	DeleteObject(myBrush);
	
}

void Bullet::Release()
{
}

