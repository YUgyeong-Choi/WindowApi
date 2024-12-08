#include "pch.h"
#include "CBlockItem.h"
#include "CObjectManager.h"
#include "CAbstractFactory.h"
#include "CItemDH.h"
#include "CMushRoom.h"
#include "CFlower.h"
#include "CBitmapManager.h"

CBlockItem::CBlockItem() : m_bContain(true), m_eItemType(ITEM_END)
{
}

CBlockItem::~CBlockItem()
{
	Release();
}

void CBlockItem::Initialize()
{
	m_tInfo = { m_tInfo.fX, m_tInfo.fY, 50.f, 50.f };
	m_BlockType = BLOCK_ITEM;
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

	float	offset = CScrollManager::GetInstance()->GetScrollX();
	HDC		hMemDC = CBitmapManager::GetInstance()->FindImage(L"Box");
	GdiTransparentBlt(hDC,			// ���� ���� DC
		m_tRect.left + (int)offset,	// ���� ���� ��ġ ��ǥ X, Y	
		m_tRect.top,
		(int)m_tInfo.fCX,			// ���� ���� �̹����� ����, ����
		(int)m_tInfo.fCY,
		hMemDC,						// ������ �̹��� DC	
		0,							// ��Ʈ�� ��� ���� ��ǥ(Left, top)
		0,
		(int)16,			// ������ �̹����� ����, ����
		(int)16,
		RGB(255, 255, 255));

	if (g_bDevmode) Hitbox(hDC, m_tRect, { offset, 0 });
}

void CBlockItem::Release()
{
}

void CBlockItem::OnCollision(CObject* _op)
{
	// �� �߿� �ϳ� ��� �ϼ���
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


void CBlockItem::CreateMushRoom()
{
    // ���°Ŵ� ���߿� �ٲٱ�, �ڽ� ���� �����ϰԲ�
    CObjectManager::GetInstance()->Add_Object(OBJ_ITEM, CAbstractFactory<CMushRoom>::Create(this->GetINFO().fX, this->GetINFO().fY - 150));
}

void CBlockItem::CreateFlower()
{
    // ���°Ŵ� ���߿� �ٲٱ�, �ڽ� ���� �����ϰԲ�
    CObjectManager::GetInstance()->Add_Object(OBJ_ITEM, CAbstractFactory<CFlower>::Create(this->GetINFO().fX, this->GetINFO().fY - 150));
}
