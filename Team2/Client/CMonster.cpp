#include "pch.h"
#include "CMonster.h"

CMonster::CMonster()
{
}

void CMonster::Initialize()
{
	m_iHp = 5;
	m_tInfo = { WINCX * 0.5, WINCY * 0.5, 50.f, 50.f };
}

int CMonster::Update()
{
	if (OBJ_DEAD) return OBJ_DEAD;
	return OBJ_NOEVENT;
}

void CMonster::LateUpdate()
{
}

void CMonster::Render(HDC hDC)
{
}

void CMonster::Release()
{
}

void CMonster::OnCollision(CObject* _op)
{
}

void CMonster::OnDead()
{
}

void CMonster::Move()
{
}
