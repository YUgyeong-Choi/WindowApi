#include "pch.h"
#include "CItem.h"
#include "CScrollManager.h"

void CItem::Initialize()
{
	m_tInfo = { 0,0, 50.f, 50.f };
	m_fSpeed = 10.f;
	m_fJumpPower = 20.f;
}

int CItem::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;

	__super::UpdateRect();

	return OBJ_NOEVENT;
}

void CItem::LateUpdate()
{
}

void CItem::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
	if (g_bDevmode) Hitbox(hDC, m_tRect);
}

void CItem::Release()
{
}

void CItem::OnCollision(CObject* _op)
{
}

void CItem::OnDead()
{
}
