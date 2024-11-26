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
		m_tInfo = { 120, 120, 20.f, 20.f };
		break;
	case UP:
		m_tInfo = { 120, 120, 20.f, 20.f };
		break;
	case RIGHT:
		m_tInfo = { 680, 120, 20.f, 20.f };
		break;
	case DOWN:
		m_tInfo = { 680, 480, 20.f, 20.f };
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

bool Monster::CheckHit(list<Obj*> m_BulletList)
{
	RECT intersectRect;
	for (auto& bullet : m_BulletList) {
		RECT a = bullet->Get_Rect();
		if (IntersectRect(&intersectRect, &m_tRect, &a)) {
			return true;
		}
	}
	return false;
}
