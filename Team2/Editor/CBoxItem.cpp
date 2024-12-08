#include "pch.h"
#include "CBoxItem.h"

CBoxItem::CBoxItem()
{
}

CBoxItem::~CBoxItem()
{
	Release();
}

void CBoxItem::Initialize()
{
	m_tInfo = { m_tInfo.fX, m_tInfo.fY, 50.f, 50.f };
	
}

int CBoxItem::Update()
{
	if (m_bIsDead == true)
	{
		return OBJ_DEAD;
	}

	__super::UpdateRect();
	return OBJ_NOEVENT;
}

void CBoxItem::LateUpdate()
{
}

void CBoxItem::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
	if (g_bDevmode) Hitbox(hDC, m_tRect);
}

void CBoxItem::Release()
{
}

void CBoxItem::OnCollision(CObject* _op)
{
}

void CBoxItem::OnBlockEvent()
{
		
}
