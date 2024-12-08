#include "pch.h"
#include "CMonster.h"

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

bool CMonster::FindPlayer()
{
	if (m_pTarget->GetINFO().fX >= m_tInfo.fX + 500 || m_pTarget->GetINFO().fX <= m_tInfo.fX - 500) // 범위 밖이라면 멈추게
		return false;
	else
		return true;
}
