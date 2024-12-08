#include "pch.h"
#include "CBoxItem.h"
#include "CObjectManager.h"
#include "CAbstractFactory.h"
#include "CItemDH.h"
#include "CMushRoom.h"
#include "CFlower.h"

CBoxItem::CBoxItem() : m_bContain(true), m_eItemType(ITEM_END)
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
    if (OBJ_PLAYER == _op->GetOBJID())
    {
        // 플레이어가 아래있으면 아이템 생성하고 다시 못 생성하게 바꾸기
        if (m_tInfo.fY < _op->GetINFO().fY)
        {
            if (m_bContain)
            {
                //CreateMushRoom();
                CreateFlower();
                m_bContain = false;
            }

        }
    }
    if (OBJ_MONSTER == _op->GetOBJID())
    {
        // 몬스터 박스 충돌 뭔가 하고 싶으면 넣으면 될듯?
    }
}

void CBoxItem::OnBlockEvent()
{
	CObjectManager::GetInstance()->Add_Object(OBJ_ITEM, CAbstractFactory<CItemDH>::Create(m_tInfo.fX, m_tInfo.fY));
	SetIsDead(true);	
}

void CBoxItem::CreateMushRoom()
{
    // 빼는거는 나중에 바꾸기, 박스 위에 생성하게끔
    CObjectManager::GetInstance()->Add_Object(OBJ_ITEM, CAbstractFactory<CMushRoom>::Create(this->GetINFO().fX, this->GetINFO().fY - 150));
}

void CBoxItem::CreateFlower()
{
    // 빼는거는 나중에 바꾸기, 박스 위에 생성하게끔
    CObjectManager::GetInstance()->Add_Object(OBJ_ITEM, CAbstractFactory<CFlower>::Create(this->GetINFO().fX, this->GetINFO().fY - 150));
}
