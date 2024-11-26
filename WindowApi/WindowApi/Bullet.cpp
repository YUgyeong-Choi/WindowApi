#include "Bullet.h"

Bullet::Bullet():m_dir(Direction::NONE)
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

void Bullet::Update()
{

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

bool Bullet::CheckOut()
{
	if (m_tRect.left <= 100) {
		return true;
	}

	if (m_tRect.top <= 100) {
		return true;
	}

	if (m_tRect.right >= WINCX - 100) {
		return true;
	}

	if (m_tRect.bottom >= WINCY - 100) {
		return true;
	}

	return false;
}
