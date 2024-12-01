#include "pch.h"
#include "MonsterB0.h"

MonsterB0::MonsterB0()
{
}

MonsterB0::~MonsterB0()
{
}

int MonsterB0::Update()
{
	++m_iTick;

	if (m_bDead) {
		return OBJ_DEAD;
	}

	//m_fSpeed += 0.0005f;
	Calc_Angle();

	if (m_iTick >= m_iFireRate) {
		Shoot_Bullet();
		m_iTick = 0;
	}

	// degree to radian
	m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));

	Obj::Update_Rect();

	return OBJ_NOEVENT;
}

void MonsterB0::Shoot_Bullet()
{
}
