#include "pch.h"
#include "CItem.h"
#include "CScrollManager.h"
#include "CObjectManager.h"
#include "CCollisionManager.h"
#include "CBitmapManager.h"
#include "CMHPlayer.h"



void CItem::Initialize()
{
	m_fVelocityX = 10.f;
	m_eOID = OBJ_ITEM;
}

int CItem::Update()
{
	if (m_bIsDead) return OBJ_DEAD;
	switch (m_eItemType)
	{
	case ITEM_NONE:
		break;
	case ITEM_MUSHROOM:
		m_tInfo.fX += m_fVelocityX;
		m_tInfo.fY += m_fVelocityY;
		break;
	case ITEM_FLOWER:
		break;
	case ITEM_STAR:
		break;
	case ITEM_CLEAR:
		break;
	case ITEM_END:
		break;
	default:
		break;
	}
	__super::UpdateRect();
	return OBJ_NOEVENT;
}

void CItem::LateUpdate()
{
	float gravity = 0.98f;
	if (!CheckOnGround()) m_bIsGround = false;
	if (!m_bIsGround)
		m_fVelocityY += gravity;
}

void CItem::Render(HDC hDC)
{
	HDC hMemDC = CBitmapManager::GetInstance()->FindImage(L"Items");
	Item(hDC, hMemDC, m_tInfo, m_tRect, m_eItemType, { CScrollManager::GetInstance()->GetScrollX(), 0.f });
	if (g_bDevmode)
	{
		Hitbox(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
	}
}

void CItem::Release()
{
}

void CItem::OnCollision(CObject* _op) 
{  
	if (_op->GetID() == OBJ_BOX)
	{
		m_fVelocityX = -10.f;
	}
	if (_op->GetID() == OBJ_PLAYER)
	{
		m_bIsDead = true;
	}
}

void CItem::OnDead()
{
	
}

void CItem::Move()
{	
	
}

bool CItem::CheckOnGround()
{
	for (auto& b : CObjectManager::GetInstance()->GetList())
	{
		if (CCollisionManager::CheckRect(this, b)) return true;
	}

	return false;
}
