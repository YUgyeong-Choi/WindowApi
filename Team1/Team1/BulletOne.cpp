#include "pch.h"
#include "BulletOne.h"

BulletOne::BulletOne()
{
}

BulletOne::~BulletOne()
{
}

int BulletOne::Update()
{
	if (m_bDead) {
		return OBJ_DEAD;
	}

	m_tInfo.fX = float(m_tInfo.fX + (m_fSpeed * cosf(m_fAngle * (PI / 180.f))));
	m_tInfo.fY = float(m_tInfo.fY - (m_fSpeed * sinf(m_fAngle * (PI / 180.f))));

	Obj::Update_Rect();
	return OBJ_NOEVENT;
}
