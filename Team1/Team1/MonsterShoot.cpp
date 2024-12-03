#include "pch.h"
#include "MonsterShoot.h"
#include "BulletOne.h"

MonsterShoot::MonsterShoot() : m_pBulletList(nullptr)
{
}

MonsterShoot::~MonsterShoot()
{
    Release();
}

void MonsterShoot::Initialize()
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;
	m_fSpeed = 0.f;

	m_iHp = 20;
	m_iDamage = 1;

	m_iDir = rand() % 2 * 2;
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

int MonsterShoot::Update()
{
	if (m_bDead) {
		return OBJ_DEAD;
	}

	m_fSpeed += 0.015f; // 되면 set, getAccel 만들어서 바꾸기

	float   fWidth(0.f), fHeight(0.f), fDiagonal(0.f), fRadian(0.f);

	fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
	fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;

	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	fRadian = acosf(fWidth / fDiagonal);

	m_fAngle = fRadian * (180.f / PI);

	if (m_pTarget->Get_Info().fY > m_tInfo.fY)
		m_fAngle *= -1.f;

	// degree to radian
	m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));

	
	
	Obj::Update_Rect();

	return OBJ_NOEVENT;
}

void MonsterShoot::Late_Update()
{
	if (m_iHp <= 0) {
		m_bDead = true;
	}

	if (!m_bDead)
	{
		if (m_ulTime + 500 < GetTickCount64())
		{
			Shoot();
			m_ulTime = GetTickCount64();
		}
	}
}

void MonsterShoot::Render(HDC _hdc)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(200, 103, 163));
	HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, myBrush);
	Rectangle(_hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(_hdc, oldBrush);
	DeleteObject(myBrush);
}

void MonsterShoot::Release()
{
}

Obj* MonsterShoot::Create_Bullet()
{
	Obj* pBullet = new BulletOne();
	pBullet->Initialize();
	static_cast<Bullet*>(pBullet)->Set_Type(BM_MONSTER);
	
	return pBullet;
}

void MonsterShoot::Shoot()
{
	m_pBulletList->push_back(Create_Bullet());
	m_pBulletList->back()->Set_Angle(m_fAngle);
	m_pBulletList->back()->Set_Pos(m_tInfo.fX , m_tInfo.fY);
}


