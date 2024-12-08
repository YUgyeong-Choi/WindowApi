#include "pch.h"
#include "CBox.h"
#include "CScrollManager.h"
#include "CBitmapManager.h"
#include "CObjectManager.h"
#include "CAbstractFactory.h"
#include "CItem.h"
#include "CMHPlayer.h"

CBox::CBox()
{
}

void CBox::Initialize()
{
	m_tInfo.fCX = 16.f;
	m_tInfo.fCY = 16.f;
	m_eOID = OBJ_BOX;
	m_eItemType = ITEM_MUSHROOM;
	m_bCanHit = true;
	CBitmapManager::GetInstance()->InsertBitmap(RESORUCEBLOCKPATH, L"Box");
}

int CBox::Update()
{
	__super::UpdateRect();
	return OBJ_NOEVENT;
}

void CBox::LateUpdate()
{
}

void CBox::Render(HDC hDC)
{
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
	/*if (m_eBoxType == BOX_BREAK)
	{
		Rectangle(hDC, m_tRect, { offset, 0 }, 0, 0, RGB(255, 0, 0));
	}
	else if (m_eBoxType == BOX_NONE)
	{
		Rectangle(hDC, m_tRect, { offset, 0 }, 0, 0, RGB(255, 255, 255));
	}
	else if (m_eBoxType == BOX_ITEM)
	{
		Rectangle(hDC, m_tRect, { offset, 0 }, 0, 0, RGB(0, 0, 255));
	}*/
	
	if (g_bDevmode) Hitbox(hDC, m_tRect, { offset, 0 });
}


void CBox::Release()
{
}

void CBox::OnCollision(CObject* _op)
{
	if (m_bCanHit && _op->GetID() == OBJ_PLAYER)
	{
		if (m_eItemType != ITEM_NONE)
		{
			CObjectManager::GetInstance()->Add_Object(OBJ_ITEM, CAbstractFactory<CItem>::Create(m_tInfo.fX, m_tInfo.fY - m_tInfo.fCY, Vector<float>{50.f, 50.f}, m_eItemType));
			m_bCanHit = false;
		}
	}
}

void CBox::OnDead()
{

}

