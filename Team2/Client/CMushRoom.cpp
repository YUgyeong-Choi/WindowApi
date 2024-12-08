#include "pch.h"
#include "CMushRoom.h"
#include "CScrollManager.h"
#include "CObjectManager.h"
#include "CCollisionManager.h"
#include "CPlayerDH.h"

CMushRoom::CMushRoom() : m_fVelocityX(0.f), m_fVelocityY(0.f)
{
	m_eItemType = ITEM_MUSHROOM;
	SetActionStatus(AS_FALL);
	m_fFallSpeed = 10.f;
}

CMushRoom::~CMushRoom()
{
}

int CMushRoom::Update()
{


	if (m_bIsDead)
		return OBJ_DEAD;

	if (m_eAction == AS_FALL) {
		m_tInfo.fY += m_fFallSpeed;
	}

	if (m_eAction == AS_STOP) {
		m_tInfo.fX += m_fSpeed;
		if (m_tInfo.fX > 300 || m_tInfo.fX < 100) {
			m_fSpeed *= -1;
		}
		SetActionStatus(AS_FALL);
	}

	__super::UpdateRect();

	return OBJ_NOEVENT;
}

void CMushRoom::LateUpdate()
{
}

void CMushRoom::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
	if (g_bDevmode) Hitbox(hDC, m_tRect);
}

void CMushRoom::OnCollision(CObject* _op)
{
	if (OBJ_PLAYER == _op->GetOBJID())
	{
		
		static_cast<CPlayerDH*>(_op)->SetPlayerState(PS_BIG);
		// 크기 수정 필요
		(_op)->SetSize(100.f, 100.f);

		SetIsDead(true);
	}
}

void CMushRoom::Move()
{
}

bool CMushRoom::CheckOnGround()
{
	for (auto& b : CObjectManager::GetInstance()->GetList())
	{
		if (CCollisionManager::CheckRect(this, b)) return true;
	}

	return false;
}
