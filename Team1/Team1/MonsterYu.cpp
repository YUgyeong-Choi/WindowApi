#include "pch.h"
#include "MonsterYu.h"

MonsterYu::MonsterYu() :m_iPatternCycle(0), m_iPattern(0), m_iShootRate(0), m_pMonsterList(nullptr)
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
	m_tInfo.fX = 300;
	m_tInfo.fY = 50.f;
	m_fSpeed = 60.f;

	m_iHp = 1000;
	m_iDamage = 1;

	m_iShootRate = 800;
	m_iPatternCycle = 0;
}

int MonsterYu::Update()
{
	if (m_bDead) {
		return OBJ_DEAD;
	}

	m_fAngle = Cal_Angle(m_pTarget->Get_Info().fX, m_pTarget->Get_Info().fY);

	Obj::Update_Rect();

	return OBJ_NOEVENT;
}

void MonsterYu::Late_Update()
{
	if (m_iHp <= 0) {
		m_bDead = true;
	}

	if (m_ulTime + m_iShootRate < GetTickCount64()){
		switch (m_iPattern)
		{
		case RAIN:
			if (m_iPatternCycle == 0) {
				m_iPatternCycle = 10;
			}
			Pattern1();
			break;
		case MISSILE:
			if (m_iPatternCycle == 0) {
				m_iPatternCycle = 15;
			}
			Pattern2();
			break;
		case BABY:
			if (m_iPatternCycle == 0) {
				m_iPatternCycle = -1;
			}
			if (m_tInfo.fX == 300 && m_tInfo.fY == 550) {
				m_iPatternCycle = 0;
			}
			else {
				Pattern3();
			}
			break;
		case CIRCLE:
			if (m_iPatternCycle == 0) {
				m_iPatternCycle = -1;
			}
			if (m_tInfo.fX == 300 && m_tInfo.fY == 50) {
				m_iPatternCycle = 0;
			}
			else {
				Pattern4();
			}
			break;
		default:
			break;
		}

		if (m_iPatternCycle == 0) {
			m_iPattern++;
			if (m_iPattern == 4) {
				m_iPattern = 0;
			}
		}
		m_ulTime = GetTickCount64();
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

float MonsterYu::Cal_Angle(float _x, float _y)
{
	float _fAngle = 0;
	float   fWidth(0.f), fHeight(0.f), fDiagonal(0.f), fRadian(0.f);

	fWidth =  _x - m_tInfo.fX;
	fHeight =  _y - m_tInfo.fY;

	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	fRadian = acosf(fWidth / fDiagonal);

	_fAngle = fRadian * (180.f / PI);

	if (_y > m_tInfo.fY)
		_fAngle *= -1.f;

	return _fAngle;
}

void MonsterYu::Pattern1()
{
	m_fSpeed = 20.f;
	m_iShootRate = 800;
	Shoot(m_fAngle - 50);
	Shoot(m_fAngle - 40);
	Shoot(m_fAngle - 30);
	Shoot(m_fAngle - 20);
	Shoot(m_fAngle - 10);
	Shoot(m_fAngle);
	Shoot(m_fAngle + 10);
	Shoot(m_fAngle + 20);
	Shoot(m_fAngle + 30);
	Shoot(m_fAngle + 40);
	Shoot(m_fAngle + 50);
	m_iPatternCycle--;
}

void MonsterYu::Pattern2()
{
	m_fSpeed = 60.f;
	m_iShootRate = 800;
	m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));
	Shoot(m_fAngle-10);
	Shoot(m_fAngle);
	Shoot(m_fAngle +10);
	m_iPatternCycle--;
}

void MonsterYu::Pattern3()
{
	m_fSpeed = 20.f;
	m_iShootRate = 1500;
	float _fAngle = Cal_Angle(300, 550);
	m_tInfo.fX += m_fSpeed * cosf(_fAngle * (PI / 180.f));
	m_tInfo.fY -= m_fSpeed * sinf(_fAngle * (PI / 180.f));
	if ((290 <= m_tInfo.fX && m_tInfo.fX <= 310) && (540 <= m_tInfo.fY && m_tInfo.fY <= 560)) {
		m_tInfo.fX = 300;
		m_tInfo.fY = 550;
	}

	SpawnMonster(m_tInfo.fX - 40, m_tInfo.fY);
	SpawnMonster(m_tInfo.fX + 40, m_tInfo.fY);

}

void MonsterYu::Pattern4()
{
	m_fSpeed = 20.f;
	m_iShootRate = 800;
	float _fAngle = Cal_Angle(300, 50);
	m_tInfo.fX += m_fSpeed * cosf(_fAngle * (PI / 180.f));
	m_tInfo.fY -= m_fSpeed * sinf(_fAngle * (PI / 180.f));
	if ((290 <= m_tInfo.fX && m_tInfo.fX <= 310) && (40 <= m_tInfo.fY && m_tInfo.fY <= 60)) {
		m_tInfo.fX = 300.f;
		m_tInfo.fY = 50;
	}

	for (int i = 0; i < 18; ++i) {
		Shoot(20 * i);
	}
}

void MonsterYu::SpawnMonster(float _x, float _y)
{
	m_pMonsterList->push_back(new MonsterShoot());
	m_pMonsterList->back()->Initialize();
	m_pMonsterList->back()->Set_Target(m_pTarget);
	m_pMonsterList->back()->Set_Pos(_x, _y);
	static_cast<MonsterYu*>(m_pMonsterList->back())->Set_Bullet(m_pBulletList);
}


void MonsterYu::Shoot(float _fAngle)
{
	m_pBulletList->push_back(Create_Bullet());
	m_pBulletList->back()->Set_Angle(_fAngle);
	m_pBulletList->back()->Set_Pos(m_tInfo.fX, m_tInfo.fY);
}
