#include "pch.h"
#include "Monster.h"

Monster::Monster():m_dir(NODIR)
{
}

Monster::~Monster()
{
	Release();
}

void Monster::Initialize()
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;
	m_fSpeed = 5.f;

	m_iHp = 10;

	m_dir = rand() % 4;
	int iXorY = 0;

	switch (m_dir)
	{
	case LEFT:
		iXorY = rand() % GAME_WINCY + GAME_WIN_TOP;
		m_tInfo.fX = GAME_WIN_LEFT + m_tInfo.fCX;
		m_tInfo.fY = iXorY;
		break;
	case TOP:
		iXorY = rand() % GAME_WINCX + GAME_WIN_LEFT;
		m_tInfo.fY = GAME_WIN_TOP + m_tInfo.fCY;
		m_tInfo.fX = iXorY;
		break;
	case RIGHT:
		iXorY = rand() % GAME_WINCY + GAME_WIN_TOP;
		m_tInfo.fX = GAME_WIN_RIGHT - m_tInfo.fCX;
		m_tInfo.fY = iXorY;
		break;
	case BOTTOM:
		iXorY = rand() % GAME_WINCX + GAME_WIN_LEFT;
		m_tInfo.fY = GAME_WIN_BOTTOM - m_tInfo.fCY;
		m_tInfo.fX = iXorY;
		break;
	case NODIR:
		break;
	default:
		break;
	}
}

int Monster::Update()
{
	if (m_bDead) {
		return OBJ_DEAD;
	}

	Obj::Update_Rect();

	return OBJ_NOEVENT;
}

void Monster::Late_Update()
{
	if (m_iHp <= 0) {
		m_bDead = true;
	}
}

void Monster::Render(HDC _hdc)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 103, 163));
	HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, myBrush);
	Rectangle(_hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(_hdc, oldBrush);
	DeleteObject(myBrush);
}

void Monster::Release()
{
}
