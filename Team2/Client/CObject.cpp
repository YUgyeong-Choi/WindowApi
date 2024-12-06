#include "pch.h"
#include "CObject.h"

CObject::CObject() : 
	m_bIsDead(false), 
	m_fSpeed(0.f), m_fAngle(0.f), m_ullTime(0), m_fJumpPower(0.f), m_fTime(0.f), m_iLevel(0), m_iHp(0),
	m_tDir(0.f, 0.f),
	m_eOID(OBJID::OBJ_NONE), m_pTarget(nullptr)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
}

void CObject::UpdateRect()
{
	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}

void CObject::OnCollision(CObject* _op)
{
}

void CObject::OnDead()
{
}
