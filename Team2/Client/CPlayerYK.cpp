#include "pch.h"
#include "CPlayerYK.h"
#include "CKeyManager.h"
#include "CCollisionManager.h"
#include "CScrollManager.h"
#include "CBitmapManager.h"
#include "CObjectManager.h"
#include "CAbstractFactory.h"
#include "CPlayerBullet.h"
#include "CItem.h"

CPlayerYK::CPlayerYK() : m_ePlayerStatus(PS_END), friction(0), m_iAnimationTime(0), m_iFireRate(0), m_iTick(0)
{
}

void CPlayerYK::Initialize()
{
	m_tInfo = { 150, 10, 40.f, 40.f };
	m_fSpeed = 8.f;
	//m_fJumpPower = 25.f;
	m_fTime = 0.f;
	m_bIsGround = false;
	m_tDir = { 0 , 1 };
	friction = 0.8f;
	m_ePlayerStatus = PS_FIRE;
	m_tInfo.fCX = 52.f;
	m_tInfo.fCY = 70.f;
	m_iAnimationTime = 0;
	m_eAction = AS_STOP;
	m_iFireRate = 13;
	m_iTick = 0;
	m_bIsDirLeft = false;
	m_iHp = 100;
}

int CPlayerYK::Update()
{
	if (m_bIsDead) {
		return OBJ_DEAD;
	}
	KeyInput();
	m_tInfo.fX += m_tDir.GetX() * m_fSpeed;
	m_tInfo.fY += m_tDir.GetY() * m_fSpeed;
	m_fTime += 0.2f;
	++m_iTick;
	if (m_eAction != AS_STOP) m_iAnimationTime += (int)m_fSpeed;
	__super::UpdateRect();
	return OBJ_NOEVENT;
}

void CPlayerYK::LateUpdate()
{
	if (!m_bIsGround && m_fTime >= 2.f) m_tDir.SetY(1);
	if (m_bIsGround) {
		m_tDir.SetX(m_tDir.GetX() * friction);
	}
	if (m_iHp < 0) {
		SetIsDead(true);
	}
	
	ScrollOffset();
}

void CPlayerYK::Render(HDC hDC)
{
	float	offset = CScrollManager::GetInstance()->GetScrollX();
	HDC		hMemDC;

	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Rectangle(hDC, m_tInfo.fX - 50 + CScrollManager::GetInstance()->GetScrollX(), m_tInfo.fY - 70, m_tInfo.fX + 50 + CScrollManager::GetInstance()->GetScrollX(), m_tInfo.fY - 60);
	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);

	myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Rectangle(hDC, m_tInfo.fX - 50 + CScrollManager::GetInstance()->GetScrollX(), m_tInfo.fY - 70, m_tInfo.fX - 50 + CScrollManager::GetInstance()->GetScrollX() + m_iHp, m_tInfo.fY - 60);
	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);

	//Rectangle(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
	switch (m_ePlayerStatus)
	{
	default:
	case PS_SMALL:
		if (m_eAction == AS_MOVE && m_bIsDirLeft) {
			hMemDC = CBitmapManager::GetInstance()->FindImage(L"SmallMarioLeft");
		}
		else{
			hMemDC = CBitmapManager::GetInstance()->FindImage(L"SmallMarioRight");
		}
		break;
	case PS_BIG:
		if (m_bIsDirLeft) hMemDC = CBitmapManager::GetInstance()->FindImage(L"BigMarioLeft");
		else hMemDC = CBitmapManager::GetInstance()->FindImage(L"BigMarioRight");
		break;
	case PS_FIRE:
		if (m_bIsDirLeft) hMemDC = CBitmapManager::GetInstance()->FindImage(L"FireMarioLeft");
		else hMemDC = CBitmapManager::GetInstance()->FindImage(L"FireMarioRight");
		break;
	}
	Mario(hDC, hMemDC, m_tInfo, m_tRect, m_bIsDirLeft, m_eAction, m_ePlayerStatus, m_iAnimationTime, { CScrollManager::GetInstance()->GetScrollX(), 0 });
	
	//if (g_bDevmode) Hitbox(hDC, m_tRect);
	if (g_bDevmode) Hitbox(hDC, m_tRect, { offset, 0 });
}

void CPlayerYK::Release()
{
}

void CPlayerYK::OnCollision(CObject* _op)
{
	if (_op->GetOBJID() == OBJ_ITEM) {
		ITEMTYPE is = dynamic_cast<CItem*>(_op)->GetItemType();
		switch (is)
		{
		case ITEM_MUSHROOM:
			OnMushroom();
			break;
		case ITEM_FLOWER:
			OnFlower();
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
	}

	if (_op->GetOBJID() == OBJ_MONSTER) {
		m_iHp -= 5;
	}

	if (_op->GetOBJID() == OBJ_MONSTER_BULLET) {
		m_iHp -= 3;
	}

}

void CPlayerYK::OnDead()
{
}

void CPlayerYK::Jump()
{
}

void CPlayerYK::KeyInput()
{

	if (CKeyManager::GetInstance()->KeyPressing(VK_LEFT))
	{
		m_tDir.SetX(-1);
		m_eAction = AS_MOVE;
		m_bIsDirLeft = true;
	}

	if (CKeyManager::GetInstance()->KeyPressing(VK_RIGHT))
	{
		m_tDir.SetX(1);
		m_eAction = AS_MOVE;
		m_bIsDirLeft = false;
	}

	if (CKeyManager::GetInstance()->KeyDown(VK_SPACE))
	{
		if (m_bIsGround)
		{
			m_tDir.SetY(-2);
			m_bIsGround = false;
			m_fTime = 0.f;
		}
	}

	if (CKeyManager::GetInstance()->KeyPressing('A'))
	{
		if (m_ePlayerStatus == PS_FIRE) {
			if (m_iTick >= m_iFireRate) {
				Fire();
				m_iTick = 0;
			}
		}
	}

}

void CPlayerYK::ScrollOffset()
{

	int		iOffSetminX = 300;
	int		iOffSetmaxX = 500;

	int		iScrollX = (int)CScrollManager::GetInstance()->GetScrollX();

	if (iOffSetminX > m_tInfo.fX + iScrollX)
		CScrollManager::GetInstance()->SetScrollX(m_fSpeed);

	if (iOffSetmaxX < m_tInfo.fX + iScrollX)
		CScrollManager::GetInstance()->SetScrollX(-m_fSpeed);

}

void CPlayerYK::OnMushroom()
{
	if (m_ePlayerStatus == PS_SMALL)
	{
		m_ePlayerStatus = PS_BIG;
		m_tInfo.fCX = 52.f;
		m_tInfo.fCY = 70.f;
	}
}

void CPlayerYK::OnFlower()
{
	if (m_ePlayerStatus == PS_BIG || m_ePlayerStatus == PS_SMALL)
	{
		m_ePlayerStatus = PS_FIRE;
		m_tInfo.fCX = 52.f;
		m_tInfo.fCY = 70.f;
	}
}

void CPlayerYK::Fire()
{

	CObjectManager::GetInstance()->Add_Object(OBJ_PLAYER_BULLET, CAbstractFactory<CPlayerBullet>::Create(m_tInfo.fX , m_tInfo.fY));
}
