#include "pch.h"
#include "CMonsterKL.h"
#include "CScrollManager.h"

void CMonsterKL::Initialize()
{
	m_tInfo = { WINCX , WINCY * 0.5f + 100, 30.f, 30.f };
	m_fSpeed = 3.f;
	m_fJumpPower = 30.f;
}

int CMonsterKL::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;
	SelectStatus();
	SelectAction();

	__super::UpdateRect();

	return OBJ_NOEVENT;
}

void CMonsterKL::LateUpdate()
{
	if (!m_bCollision)
		SetActionStatus(AS_FALL);
}

void CMonsterKL::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
	if (g_bDevmode) Hitbox(hDC, m_tRect);
}

void CMonsterKL::Release()
{
}

void CMonsterKL::OnCollision(CObject* _op)
{
	if (OBJ_PLAYER == _op->GetOBJID())
	{
		if (m_tInfo.fY > _op->GetINFO().fY)
			SetIsDead(true);

	}
	if (OBJ_BLOCK == _op->GetOBJID())
	{
		// 이거 수정 예정
		if (m_tInfo.fY < _op->GetINFO().fY)
		{
			
			SetActionStatus(AS_STOP);
			m_fTime = 0.f;
			m_tInfo.fY = _op->GetINFO().fY - _op->GetINFO().fCY * 0.5f - GetINFO().fCY * 0.5f;
			m_bCollision = true;
		}
		else
		{
			SetActionStatus(AS_FALL);
			m_bCollision = false;
		}
	}
}

void CMonsterKL::OnDead()
{
}

void CMonsterKL::SelectAction()
{
	switch (m_eAction)
	{
	case AS_STOP:
		break;
	case AS_MOVE_LEFT:
		m_tInfo.fX -= m_fSpeed;
		m_bCollision = false;
		break;
	case AS_MOVE_RIGHT:
		m_tInfo.fX += m_fSpeed;
		m_bCollision = false;
		break;
	case AS_FALL:
		m_tInfo.fY += m_fGravity;
		break;
	case AS_JUMP:
		break;
	case AS_END:
		break;
	default:
		break;
	}
}

void CMonsterKL::SelectStatus()
{
	if (false == m_bCollision)
	{
		// 처음에 공중에서 생성해서 벽까지 이동하게
		SetActionStatus(AS_FALL);
	}
	else
	{
		// 일정 거리 안에 들어오면 움직이게
		if (m_pTarget->GetINFO().fX < m_tInfo.fX && fabs(m_pTarget->GetINFO().fX - m_tInfo.fX) < 300)
			SetActionStatus(AS_MOVE_LEFT);
		else if (m_pTarget->GetINFO().fX > m_tInfo.fX && fabs(m_pTarget->GetINFO().fX - m_tInfo.fX) < 300)
			SetActionStatus(AS_MOVE_RIGHT);
		else if (m_pTarget->GetINFO().fX == m_tInfo.fX)
			SetActionStatus(AS_STOP);
	}
}
