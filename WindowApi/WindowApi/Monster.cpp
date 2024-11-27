#include "Monster.h"

Monster::Monster():m_dir(DIR::NONE)
{
}

Monster::Monster(DIR _dir):m_dir(_dir)
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

int Monster::Update()
{
	if (m_bDead) {
		return OBJ_DEAD;
	}
	switch (m_dir)
	{
	case LEFT:
	case RIGHT:
		m_tInfo.fY += m_fSpeed;
		break;
	case UP:
	case DOWN:
		m_tInfo.fX += m_fSpeed;
		break;
	case NONE:
		break;
	default:
		break;
	}
	Obj::Update_Rect();

	return OBJ_NOEVENT;
}

void Monster::LateUpdate()
{
	switch (m_dir)
	{
	case LEFT:
	case RIGHT:
		if (WINCY - 100 <= LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f))) {
			m_fSpeed *= -1;
		}
		if (100 >= LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f))) {
			m_fSpeed *= -1;
		}
		break;
	case UP:
	case DOWN:
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

}

void Monster::Render(HDC _hdc)
{;

	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 103, 163));
	HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, myBrush);
	Rectangle(_hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(_hdc, oldBrush);
	DeleteObject(myBrush);

}

void Monster::Release()
{
}
