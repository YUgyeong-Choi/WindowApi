#include "pch.h"
#include "CItemDH.h"
#include "CScrollManager.h"

CItemDH::CItemDH()
{
}

void CItemDH::Initialize()
{
	m_tInfo = { 200.f, 200.f, 30.f, 30.f };
	m_fJumpPower = 5.f;
	m_fCurrentGravity = m_fGravity;
	m_eAction = ACTIONSTATUS::AS_JUMP;
}

int CItemDH::Update()
{
	if (m_bIsDead == true)
	{
		return OBJ_DEAD;
	}

	switch (m_eAction)
	{
	case AS_JUMP:
	{
		// ���� �ð� �� ����.
		if (m_fTime < 0.5f)
		{
			// ���� �ð��ϰ��� 2�ʱ���.
			m_tInfo.fY -= (m_fJumpPower * sinf(90.f * (PI / 180.f)) * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.5f;
		}
		else
		{
			// 2�� �Ŀ� �߷� �ӵ���ŭ �������� ��.
			m_tInfo.fY += m_fCurrentGravity;
		}

		m_fTime += 0.05f;
		break;
	}
	}

	// ���� ���°� �ƴ� ��쿡�� �߷¿� ������ �޴´�.
	if (m_eAction != AS_JUMP)
	{
		m_tInfo.fY += m_fCurrentGravity;
	}

	__super::UpdateRect();
	return OBJ_NOEVENT;
}

void CItemDH::LateUpdate()
{
}

void CItemDH::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
	if (g_bDevmode) Hitbox(hDC, m_tRect);
}

void CItemDH::Release()
{
}

void CItemDH::OnCollision(CObject* _op)
{
	switch (_op->GetOBJID())
	{
	case OBJID::OBJ_PLAYER:
	{
		m_bIsDead = true;
	}
		break;

	case OBJID::OBJ_BLOCK:
	{		
		if (m_tInfo.fY < _op->GetINFO().fY)
		{
			// ���� ������ �浹.
			// ������ ������ �÷��̾� ���� ����.
			// ���� �ð� �ʱ�ȭ
			m_fTime = 0.f;
			m_eAction = ACTIONSTATUS::AS_STOP;
			m_tInfo.fY = _op->GetRECT()->top - (m_tInfo.fCY * 0.55f);
		}
	}
	break;
	default:
		break;
	}
}

void CItemDH::OnDead()
{

}
