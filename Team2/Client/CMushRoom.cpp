#include "pch.h"
#include "CMushRoom.h"
#include "CScrollManager.h"
#include "CPlayer.h"

CMushRoom::CMushRoom()
{
}

CMushRoom::~CMushRoom()
{
}

int CMushRoom::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;

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
		
		static_cast<CPlayer*>(_op)->SetPlayerState(PS_BIG);
		// 크기 수정 필요
		(_op)->SetSize(100.f, 100.f);

		SetIsDead(true);
	}
}