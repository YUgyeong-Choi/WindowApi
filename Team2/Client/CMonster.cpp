#include "pch.h"
#include "CMonster.h"

CMonster::CMonster() : m_bActive(false)
{
}

void CMonster::Initialize()
{
}

int CMonster::Update()
{
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
