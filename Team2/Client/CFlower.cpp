#include "pch.h"
#include "CFlower.h"
#include "CScrollManager.h"
#include "CPlayer.h"

CFlower::CFlower()
{
}

CFlower::~CFlower()
{
}

void CFlower::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
	if (g_bDevmode) Hitbox(hDC, m_tRect);
}

void CFlower::OnCollision(CObject* _op)
{
	if (OBJ_PLAYER == _op->GetOBJID())
	{
		static_cast<CPlayer*>(_op)->SetPlayerState(PS_FIRE);
		(_op)->SetSize(150.f, 150.f);

		SetIsDead(true);
	}
}
