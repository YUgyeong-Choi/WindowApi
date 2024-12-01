#include "pch.h"
#include "MonsterYu.h"

MonsterYu::MonsterYu()
{
}

MonsterYu::~MonsterYu()
{
	Release();
}

void MonsterYu::Initialize()
{
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
	m_tInfo.fX = GAME_WIN_RIGHT / 2;
	m_tInfo.fY = 300.f;
	m_fSpeed = 0.f;

	m_iHp = 1000;
	m_iDamage = 10;
}

int MonsterYu::Update()
{
	if (m_bDead) {
		return OBJ_DEAD;
	}

	Cal_Angle();

	if (m_ulTime + 500 < GetTickCount64())
	{
		switch (0)
		{
		case 0:
			Pattern1();
			break;
		case 1:
			Pattern2();
			break;
		case 2:
			Pattern3();
			break;
		case 3:
			Pattern4();
			break;
		default:
			break;
		}
		m_ulTime = GetTickCount64();
	}

	Obj::Update_Rect();

	return OBJ_NOEVENT;
}

void MonsterYu::Late_Update()
{
	if (m_iHp <= 0) {
		m_bDead = true;
	}
}

void MonsterYu::Set_Hp(int _iDamage)
{
	m_iHp += _iDamage;
	if (m_iHp > 1000) {
		m_iHp = 1000;
	}
}

void MonsterYu::Render(HDC _hdc)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(200, 103, 163));
	HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, myBrush);
	Rectangle(_hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(_hdc, oldBrush);
	DeleteObject(myBrush);
}

void MonsterYu::Release()
{
}

void MonsterYu::Cal_Angle()
{
	float   fWidth(0.f), fHeight(0.f), fDiagonal(0.f), fRadian(0.f);

	fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
	fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;

	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	fRadian = acosf(fWidth / fDiagonal);

	m_fAngle = fRadian * (180.f / PI);

	if (m_pTarget->Get_Info().fY > m_tInfo.fY)
		m_fAngle *= -1.f;

	// degree to radian
	//m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
	//m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));
}

void MonsterYu::Pattern1()
{
	Shoot(0);
}

void MonsterYu::Pattern2()
{
}

void MonsterYu::Pattern3()
{
}

void MonsterYu::Pattern4()
{
}


void MonsterYu::Shoot(float _fAngle)
{
	m_pBulletList->push_back(Create_Bullet());
	m_pBulletList->back()->Set_Angle(_fAngle);
	m_pBulletList->back()->Set_Pos(m_tInfo.fX, m_tInfo.fY);
}
