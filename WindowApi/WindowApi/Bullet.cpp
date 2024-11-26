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
	Ellipse(_hdc,m_tRect.left,m_tRect.top,m_tRect.right,m_tRect.bottom);
}

void Bullet::Release()
{
}
