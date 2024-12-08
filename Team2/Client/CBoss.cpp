#include "pch.h"
#include "Define.h"
#include "CBoss.h"
#include "CMHPlayer.h"
#include "CPlayer.h"
#include "CObjectManager.h"
#include "CCollisionManager.h"
#include "CScrollManager.h"

CBoss::CBoss() : m_fDistance(0.f), m_bCanHit(true)
{
}

void CBoss::Initialize()
{
	m_tInfo = { 700, 400, 100.f, 100.f };
	m_fSpeed = 5.f;
	m_bIsGround = false;
	m_eOID = OBJ_MONSTER;
}

int CBoss::Update()
{
    if (m_bIsDead && !m_bIsActive) return OBJ_DEAD;
	
	m_tInfo.fX += m_fVelocityX;
	m_tInfo.fY += m_fVelocityY;
	
	__super::UpdateRect();
    return OBJ_NOEVENT;
}

void CBoss::LateUpdate()
{
	if (!CheckOnGround()) m_bIsGround = false;
	if (!m_bIsGround) m_fVelocityY += m_fSpeed;
	if (CCollisionManager::DetectPlayer(this, CObjectManager::GetInstance()->GetPlayer())) m_pTarget = CObjectManager::GetInstance()->GetPlayer();
	else m_pTarget = nullptr;

	Pattern1();
}

void CBoss::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0.f}, 0.f, 0.f, RGB(255, 0, 255));
}

void CBoss::Release()
{
}

void CBoss::OnCollision(CObject* _op)
{
	if (m_bCanHit && _op->GetID() == OBJ_PLAYER)
	{
		//This의 바닥과 Box의 위와 플레이어의 위가충돌
		//if (m_tRect.bottom > _op->GetRECT()->top && m_tRect.top < _op->GetRECT()->top)
		//{
		//	/*if (dynamic_cast<CMHPlayer*>(_op)->m_PHead.x > m_tRect.left + 10.f && dynamic_cast<CMHPlayer*>(_op)->m_PHead.x < m_tRect.right - 10.f)
		//	{
		//		m_bCanHit = false;
		//	}*/
		//}
		// This의 탑과 플레이어의 아래충돌
		if (m_tRect.top < _op->GetRECT()->bottom && m_tRect.bottom > _op->GetRECT()->bottom)
		{
			m_tInfo.fY = _op->GetRECT()->bottom + m_tInfo.fCX * 0.5f + 1.f;
		}
	}

	if (_op->GetID() == OBJ_BOX || _op->GetID() == OBJ_NONE)
	{
		//This의 바닥과 Box의 위와 지형 또는 박스의 위가충돌
		if (m_tRect.bottom > _op->GetRECT()->top && m_tRect.top < _op->GetRECT()->top)
		{
			m_tInfo.fY = _op->GetRECT()->top - m_tInfo.fCY * 0.5f + 1.f;
			m_fVelocityY = 0.f;
			m_fTime = 0.f;
			m_bIsGround = true;
			/*if (dynamic_cast<CMHPlayer*>(_op)->m_PHead.x > m_tRect.left + 10.f && dynamic_cast<CMHPlayer*>(_op)->m_PHead.x < m_tRect.right - 10.f)
			{
				m_bCanHit = false;
			}*/
		}
		// This의 탑과 플레이어의 아래충돌
		/*if (m_tRect.top < _op->GetRECT()->bottom && m_tRect.bottom > _op->GetRECT()->bottom)
		{
			m_tInfo.fY = _op->GetRECT()->bottom + m_tInfo.fCX * 0.5f + 1.f;
		}*/
	}
}

void CBoss::OnDead()
{
    m_bIsDead = true;
}

//Follow m_pTarget
void CBoss::Pattern1()
{
	if (m_pTarget)
	{
		if (m_pTarget->GetINFO().fX < m_tInfo.fX)
		{
			m_fVelocityX = -m_fSpeed;
		}
		else
		{
			m_fVelocityX = m_fSpeed;
		}
	}
}

//Fire to m_Ptarget.x
void CBoss::Pattern2()
{
	if (m_pTarget)
	{
		if (m_pTarget->GetINFO().fX < m_tInfo.fX)
		{
			m_fVelocityX = -m_fSpeed;
		}
		else
		{
			m_fVelocityX = m_fSpeed;
		}
	}
}

//Jump
void CBoss::Pattern3()
{

}

bool CBoss::CheckOnGround()
{
	for (auto& b : CObjectManager::GetInstance()->GetList())
	{
		if (CCollisionManager::CheckRect(this, b)) return true;
	}

	return false;
}
