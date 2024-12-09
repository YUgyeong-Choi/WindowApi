#include "pch.h"
#include "CItem.h"
#include "CScrollManager.h"
#include "CBitmapManager.h"

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
	HDC hMemDC = CBitmapManager::GetInstance()->FindImage(L"Items");
	Item(hDC, hMemDC, m_tInfo, m_tRect, m_eItemType, { CScrollManager::GetInstance()->GetScrollX(), 0.f });

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
