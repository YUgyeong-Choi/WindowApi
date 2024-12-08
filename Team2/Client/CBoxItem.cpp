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
        // �÷��̾ �Ʒ������� ������ �����ϰ� �ٽ� �� �����ϰ� �ٲٱ�
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
        // ���� �ڽ� �浹 ���� �ϰ� ������ ������ �ɵ�?
    }
}

void CBoxItem::OnBlockEvent()
{
	CObjectManager::GetInstance()->Add_Object(OBJ_ITEM, CAbstractFactory<CItemDH>::Create(m_tInfo.fX, m_tInfo.fY));
	SetIsDead(true);	
}

void CBoxItem::CreateMushRoom()
{
    // ���°Ŵ� ���߿� �ٲٱ�, �ڽ� ���� �����ϰԲ�
    CObjectManager::GetInstance()->Add_Object(OBJ_ITEM, CAbstractFactory<CMushRoom>::Create(this->GetINFO().fX, this->GetINFO().fY - 150));
}

void CBoxItem::CreateFlower()
{
    // ���°Ŵ� ���߿� �ٲٱ�, �ڽ� ���� �����ϰԲ�
    CObjectManager::GetInstance()->Add_Object(OBJ_ITEM, CAbstractFactory<CFlower>::Create(this->GetINFO().fX, this->GetINFO().fY - 150));
}
