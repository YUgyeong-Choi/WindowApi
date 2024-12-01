#include "pch.h"
#include "Monster.h"
#include "BulletOne.h"
#include "BulletScrew.h"

Monster::Monster():m_iDir(NODIR), m_iTick(0), m_iFireRate(0), m_pBulletList(nullptr), m_BulletDamage(0)
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
	m_fSpeed = 2.f;

	m_iHp = 10;
	m_iDamage = 10;
	m_BulletDamage = 1;

	m_iFireRate = 20;

	m_iDir = rand() % 4;
	int iXorY = 0;

	switch (m_iDir)
	{
	case LEFT:
		iXorY = rand() % int(GAME_WINCY + GAME_WIN_TOP);
		m_tInfo.fX = int(GAME_WIN_LEFT) + m_tInfo.fCX;
		m_tInfo.fY = (float)iXorY;
		break;
	case TOP:
		iXorY = rand() % int(GAME_WINCX + GAME_WIN_LEFT);
		m_tInfo.fY = int(GAME_WIN_TOP) + m_tInfo.fCY;
		m_tInfo.fX = (float)iXorY;
		break;
	case RIGHT:
		iXorY = rand() % int(GAME_WINCY + GAME_WIN_TOP);
		m_tInfo.fX = int(GAME_WIN_RIGHT) - m_tInfo.fCX;
		m_tInfo.fY = (float)iXorY;
		break;
	case BOTTOM:
		iXorY = rand() % int(GAME_WINCX + GAME_WIN_LEFT);
		m_tInfo.fY = int(GAME_WIN_BOTTOM) - m_tInfo.fCY;
		m_tInfo.fX = (float)iXorY;
		break;
	case NODIR:
		break;
	default:
		break;
	}
}

int Monster::Update()
{
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

void Monster::Calc_Angle()
{
	float   fWidth(0.f), fHeight(0.f), fDiagonal(0.f), fRadian(0.f);

	fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
	fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;

	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	fRadian = acosf(fWidth / fDiagonal);

	m_fAngle = fRadian * (180.f / PI);

	if (m_pTarget->Get_Info().fY > m_tInfo.fY)
		m_fAngle *= -1.f;
}


Obj* Monster::Create_Bullet(float _fAngle)
{
	Obj* pBullet(nullptr);
	pBullet = new BulletOne(m_fAngle + _fAngle, m_BulletDamage, OBJ_MONSTER);
	pBullet->Initialize();
	pBullet->Set_Pos(float(m_tInfo.fX), float(m_tInfo.fY));
	return pBullet;
}

Obj* Monster::Create_BulletScrew(float _fAngle)
{
	Obj* pBullet(nullptr);
	pBullet = new BulletScrew(m_fAngle - _fAngle, m_BulletDamage, OBJ_MONSTER);
	pBullet->Initialize();
	pBullet->Set_Pos(float(m_tInfo.fX), float(m_tInfo.fY));
	return pBullet;
}

void Monster::Shoot_Bullet()
{
}
