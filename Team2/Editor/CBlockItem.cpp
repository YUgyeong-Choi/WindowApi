#include "pch.h"
#include "CBlockItem.h"

CBlockItem::CBlockItem()
{
}

CBlockItem::~CBlockItem()
{
	Release();
}

void CBlockItem::Initialize()
{
	m_tInfo = { m_tInfo.fX, m_tInfo.fY, 50.f, 50.f };
	
}

int CBlockItem::Update()
{
	if (m_bIsDead == true)
	{
		return OBJ_DEAD;
	}

	__super::UpdateRect();
	return OBJ_NOEVENT;
}

void CBlockItem::LateUpdate()
{
}

void CBlockItem::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
	if (g_bDevmode) Hitbox(hDC, m_tRect);
}

void CBlockItem::Release()
{
}

void CBlockItem::OnCollision(CObject* _op)
{
}
