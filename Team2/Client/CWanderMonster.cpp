#include "pch.h"
#include "CWanderMonster.h"
#include "CCollisionManager.h"
#include "CScrollManager.h"


CWanderMonster::CWanderMonster()
{
}

CWanderMonster::~CWanderMonster()
{
}

void CWanderMonster::Initialize()
{
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
	m_fSpeed = 3.f;
	m_fJumpPower = 10.f;
	m_fTime = 0.f;
	m_ullTime = GetTickCount64();
	m_fAngle = 45.f;
	m_eAction = AS_STOP;
}

int CWanderMonster::Update()
{
	if (true == m_bIsDead)
		return OBJ_DEAD;

	CObject::UpdateRect();

	return OBJ_NOEVENT;
}

void CWanderMonster::LateUpdate()
{
	if (FindPlayer())
		SetActionStatus(AS_JUMP);
	else
		SetActionStatus(AS_STOP);

	if (m_ullTime + 3000 < GetTickCount64()) // 3초에 한 번씩 플레이어 방향으로 점프
	{
		Jump();
	}
}

void CWanderMonster::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
}

void CWanderMonster::Release()
{
}

void CWanderMonster::OnCollision(CObject* _op)
{
}

void CWanderMonster::Jump()
{
	float fY(0.f);

	bool bLineCol = CCollisionManager::CollisionLine(m_tInfo, &fY);

	if (AS_JUMP == GetActionStatus())
	{
		if (m_pTarget->GetINFO().fX <= m_tInfo.fX) // 플레이어 좌표를 따라감
		{
			m_fAngle = 90.f;
		}
		else if (m_pTarget->GetINFO().fX >= m_tInfo.fX)
		{
			m_fAngle = 45.f;
		}

		m_tInfo.fX += m_fJumpPower * cosf(m_fAngle) * m_fTime;

		m_tInfo.fY -= (m_fJumpPower * sinf(90.f) * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.5f;
		m_fTime += 0.1f;

		if (bLineCol && (fY < m_tInfo.fY))
		{
			SetActionStatus(AS_STOP);
			m_fTime = 0.f;
			m_tInfo.fY = fY - m_tInfo.fCY * 0.5f;
			m_ullTime = GetTickCount64();
		}
	}
	else if (bLineCol)
	{
		if (fY - m_tInfo.fCY * 0.5f > m_tInfo.fY)
			m_tInfo.fY += m_fSpeed;
		else
			m_tInfo.fY = fY - m_tInfo.fCY * 0.5f;
	}
}
