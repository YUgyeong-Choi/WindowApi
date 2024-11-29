#include "pch.h"
#include "BulletScrew.h"

BulletScrew::BulletScrew()
{
}

BulletScrew::~BulletScrew()
{
	Release();
}

void BulletScrew::Initialize()
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;

	m_fSpeed = 10.f;

	m_fRotAngle = 0.f;
	m_fRotSpeed = 30.f;
	m_fDistance = 20.f;

	m_bStart = true;

	m_iHp = 1;
	m_iDamage = 10;
}

int BulletScrew::Update()
{
	if (m_bDead) {
		return OBJ_DEAD;
	}

	if (m_bStart)
	{
		m_tCenter.x = (long)m_tInfo.fX;
		m_tCenter.y = (long)m_tInfo.fY;
		m_bStart = false;
	}

	m_tCenter.x += float(m_fSpeed * cosf(m_fAngle * (PI / 180.f)));
	m_tCenter.y -= float(m_fSpeed * sinf(m_fAngle * (PI / 180.f)));

	m_fRotAngle += m_fRotSpeed;

	m_tInfo.fX = m_tCenter.x + (m_fDistance * cosf(m_fRotAngle * (PI / 180.f)));
	m_tInfo.fY = m_tCenter.y - (m_fDistance * sinf(m_fRotAngle * (PI / 180.f)));

	Obj::Update_Rect();

	return OBJ_NOEVENT;
}