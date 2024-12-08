#include "pch.h"
#include "CPlayerSH.h"
#include "CBitMapManager.h"
#include "CItem.h"
#include "CCollisionManager.h"
#include "CKeyManager.h"
#include "CAbstractFactory.h"
#include "CObjectManager.h"
#include "CPlayerBullet.h"
#include "CScrollManager.h"

CPlayerSH::CPlayerSH()
{
}

void CPlayerSH::Initialize()
{
	m_tInfo = { 100, 200, 35.f, 35.f };
	m_fSpeed = 10.f;
	m_fJumpPower = 30.f;
	m_eOID = OBJ_PLAYER;
	m_eAction = AS_FALL;
	m_eStatus = PS_SMALL;
	m_fAngle = 45.f;

	CBitmapManager::GetInstance()->InsertBitmap(L"../Image/maja2.bmp", L"Player");
}

int CPlayerSH::Update()
{
	KeyInput();

	if (AS_FALL == GetActionStatus())
	{
	}

	__super::UpdateRect();
	return OBJ_NOEVENT;
}

void CPlayerSH::LateUpdate()
{

	Jump();
	ScrollOffset();

	if (PS_BIG == GetStatus())
	{
		m_tInfo.fCX = 45.f;
		m_tInfo.fCY = 45.f;
	}

	if (PS_STAR == GetStatus())
	{
	}
}

void CPlayerSH::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollManager::GetInstance()->GetScrollX();

	HDC		hMemDC = CBitmapManager::GetInstance()->FindImage(L"Player");

	GdiTransparentBlt(hDC,			// 복사 받을 DC
		m_tRect.left + iScrollX,	// 복사 받을 위치 좌표 X, Y	
		m_tRect.top,
		(int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
		(int)m_tInfo.fCY,
		hMemDC,						// 복사할 이미지 DC	
		0,							// 비트맵 출력 시작 좌표(Left, top)
		0,
		(int)m_tInfo.fCX,			// 복사할 이미지의 가로, 세로
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));		// 제거할 색상
}

void CPlayerSH::Release()
{
}

void CPlayerSH::OnCollision(CObject* _op)
{
	if (OBJ_ITEM == _op->GetOBJID())
	{
		if (CItem* Temp = dynamic_cast<CItem*>(_op))
		{
			if (Temp->GetItemType() == ITEM_STAR)
			{
				SetStatus(PS_STAR);
			}
			if (Temp->GetItemType() == ITEM_FLOWER)
			{
				if (GetStatus() == PS_SMALL)
					SetStatus(PS_BIG);
				else
					SetStatus(PS_FIRE);
			}
			if (Temp->GetItemType() == ITEM_MUSHROOM)
			{
				if (GetStatus() == PS_SMALL)
					SetStatus(PS_BIG);
				else
				{
					// 점수 증가
				}
			}
		}
		_op->SetIsDead(true);
	}
}

void CPlayerSH::OnDead()
{
}

void CPlayerSH::Jump()
{
	if (AS_JUMP == GetActionStatus())
	{
		m_tInfo.fY -= (m_fJumpPower * sinf(45.f) * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.5f;
		m_fTime += 0.2f;
	}

	if (AS_STOP == GetActionStatus())
	{
		m_fTime = 0.f;
	}
}

void CPlayerSH::KeyInput()
{
	float	fY(0.f);

	if (CKeyManager::GetInstance()->KeyPressing(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
		m_fAngle = 90.f;             // 총알 각도 조정
		if (AS_FALL == GetActionStatus())
			SetActionStatus(AS_FALL);
		else if (AS_JUMP != GetActionStatus())
			SetActionStatus(AS_MOVE_LEFT);
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
		m_fAngle = 45.f;			// 총알 각도 조정
		if (AS_FALL == GetActionStatus())
			SetActionStatus(AS_FALL);
		else if (AS_JUMP != GetActionStatus())
			SetActionStatus(AS_MOVE_RIGHT);
	}

	if (CKeyManager::GetInstance()->KeyDown(VK_SPACE))
	{
		if (AS_FALL != GetActionStatus())
			SetActionStatus(AS_JUMP);
	}

	if (GetStatus() == PS_FIRE && GetActionStatus() != AS_JUMP)
	{
		if (CKeyManager::GetInstance()->KeyPressing('D'))
		{
			if (m_ullTime + 200 < GetTickCount64())
			{
				CObjectManager::GetInstance()->Add_Object(OBJ_PLAYER_BULLET, CAbstractFactory<CPlayerBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle));
				m_ullTime = GetTickCount64();
			}
		}
	}
}

void CPlayerSH::ScrollOffset()
{

	int		iOffSetX = WINCX >> 1;

	int		iScrollX = (int)CScrollManager::GetInstance()->GetScrollX();

	if (iOffSetX > m_tInfo.fX + iScrollX)
		CScrollManager::GetInstance()->SetScrollX(m_fSpeed);

	if (iOffSetX < m_tInfo.fX + iScrollX)
		CScrollManager::GetInstance()->SetScrollX(-m_fSpeed);

	/*int		iOffSetminX = 300;
	int		iOffSetmaxX = 500;

	int		iScrollX = (int)CScrollManager::GetInstance()->GetScrollX();

	if (iOffSetminX > m_tInfo.fX + iScrollX)
		CScrollManager::GetInstance()->SetScrollX(m_fSpeed);

	if (iOffSetmaxX < m_tInfo.fX + iScrollX)
		CScrollManager::GetInstance()->SetScrollX(-m_fSpeed);*/

}