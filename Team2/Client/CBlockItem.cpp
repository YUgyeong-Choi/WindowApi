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
	GdiTransparentBlt(hDC,			// 복사 받을 DC
		m_tRect.left + (int)offset,	// 복사 받을 위치 좌표 X, Y	
		m_tRect.top,
		(int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
		(int)m_tInfo.fCY,
		hMemDC,						// 복사할 이미지 DC	
		0,							// 비트맵 출력 시작 좌표(Left, top)
		0,
		(int)16,			// 복사할 이미지의 가로, 세로
		(int)16,
		RGB(255, 255, 255));

	if (g_bDevmode) Hitbox(hDC, m_tRect, { offset, 0 });
}

void CBlockItem::Release()
{
}

void CBlockItem::OnCollision(CObject* _op)
{
	// 둘 중에 하나 골라서 하세요
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


void CBlockItem::CreateMushRoom()
{
    // 빼는거는 나중에 바꾸기, 박스 위에 생성하게끔
    CObjectManager::GetInstance()->Add_Object(OBJ_ITEM, CAbstractFactory<CMushRoom>::Create(this->GetINFO().fX, this->GetINFO().fY - 150));
}

void CBlockItem::CreateFlower()
{
    // 빼는거는 나중에 바꾸기, 박스 위에 생성하게끔
    CObjectManager::GetInstance()->Add_Object(OBJ_ITEM, CAbstractFactory<CFlower>::Create(this->GetINFO().fX, this->GetINFO().fY - 150));
}
