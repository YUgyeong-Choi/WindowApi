#include "pch.h"
#include "Obj.h"

Obj::Obj() : m_fSpeed(0.f), m_bDead(false), m_fAngle(0.0f), m_fDistance(0), m_pTarget(nullptr), m_iHp(0), m_iDamage(0), m_fAccel(0.f)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
}

Obj::~Obj()
{
}

void Obj::Set_Hp(int _iDamage)
{
	m_iHp += _iDamage;
	if (m_iHp > 100) {
		m_iHp = 100;
	}
}

void Obj::Update_Rect()
{
	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}
