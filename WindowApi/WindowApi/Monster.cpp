#include "Monster.h"

Monster::Monster():m_dir(Direction::NONE)
{
}

Monster::Monster(Direction _dir):m_dir(_dir)
{}

Monster::~Monster()
{
	Release();
}

void Monster::Initialize()
{
	switch (m_dir)
	{
	case LEFT:
		m_tInfo = { 110, 110, 15.f, 15.f };
		break;
	case UP:
		m_tInfo = { 110, 110, 15.f, 15.f };
		break;
	case RIGHT:
		m_tInfo = { 690, 110, 15.f, 15.f };
		break;
	case DOWN:
		m_tInfo = { 110, 490, 15.f, 15.f };
		break;
	case NONE:
		break;
	default:
		break;
	}
	m_fSpeed = 5.f;
}

void Monster::Update()
{
	switch (m_dir)
	{
	case LEFT:
	case RIGHT:
		m_tInfo.fY += m_fSpeed;
		if (WINCY - 100 <= LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f))) {
			m_fSpeed *= -1;
		}
		if (100 >= LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f))) {
			m_fSpeed *= -1;
		}
		break;
	case UP:
	case DOWN:
		m_tInfo.fX += m_fSpeed;
		if (WINCX - 100 <= LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f))) {
			m_fSpeed *= -1;
		}

		if (100 >= LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f))) {
			m_fSpeed *= -1;
		}
		break;
	case NONE:
		break;
	default:
		break;
	}
	Obj::Update_Rect();
}

void Monster::Render(HDC _hdc)
{
	Rectangle(_hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void Monster::Release()
{
}
