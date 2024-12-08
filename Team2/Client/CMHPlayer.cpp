#include "pch.h"
#include "CMHPlayer.h"
#include "CKeyManager.h"
#include "CCollisionManager.h"
#include "CScrollManager.h"
#include "CLineManager.h"
#include "CBitmapManager.h"
#include "CObjectManager.h"
#include "CAbstractFactory.h"
#include "CProjectile.h"

float gravity = 0.0f;
float friction = 0.8f;
float jump = -15.f;

CMHPlayer::CMHPlayer() : m_fVelocityX(0.f), m_fVelocityY(0.f), m_iAnimationTime(0), m_ullLastFire(0), m_ullFireDelay(0)
{
}

void CMHPlayer::Initialize()
{
	m_tInfo = { WINCX * 0.5f, WINCY * 0.5f, 40.f, 40.f };
	m_fSpeed = 10.f;
	m_fJumpPower = 20.f;
	//m_bIsFalling = true;
	m_eOID = OBJ_PLAYER;
	m_eActionStatus = AS_STOP;
	m_ullFireDelay = 100;
	m_fTime = 0.f;
	m_iAnimationTime = 0;
	m_bIsGround = false;
	m_bFacingLeft = true;
	m_fVelocityY = 0;
	m_tDir = { 0 , 1 };
}

int CMHPlayer::Update()
{
	if (m_bIsDead) return OBJ_DEAD; 
	KeyInput();
	
	m_tInfo.fX += m_tDir.x * m_fSpeed;
	m_tInfo.fY += m_tDir.y * m_fSpeed;
	/*m_PHead.x = m_tInfo.fX;
	m_PHead.y = m_tRect.top;*/
	m_fTime += 0.2f;
	if (m_eActionStatus != AS_STOP) m_iAnimationTime += (int)m_fSpeed;
	if (!m_bIsGround) m_eActionStatus = AS_JUMP;
	__super::UpdateRect();
	return OBJ_NOEVENT;
}

void CMHPlayer::LateUpdate()
{
	if (!m_bIsGround && m_fTime >= 2.f) m_tDir.y = 1;
	if (m_bIsGround) {
		m_tDir.x *= friction;
	}
	//Jump();
	ScrollOffset();
	if (m_tInfo.fY >= 2000.f)
	{
		m_tInfo.fY = 0.f;
		m_bIsGround = false;
	}
	
}

void CMHPlayer::Render(HDC hDC)
{
	HDC		hMemDC;
	switch (m_ePlayerStatus)
	{
	default:
	case PS_SMALL:
		if(m_bFacingLeft) hMemDC = CBitmapManager::GetInstance()->FindImage(L"SmallMarioLeft");
		else hMemDC = CBitmapManager::GetInstance()->FindImage(L"SmallMarioRight");
		break;
	case PS_BIG:
		if (m_bFacingLeft) hMemDC = CBitmapManager::GetInstance()->FindImage(L"BigMarioLeft");
		else hMemDC = CBitmapManager::GetInstance()->FindImage(L"BigMarioRight");
		break;
	case PS_FIRE:
		if (m_bFacingLeft) hMemDC = CBitmapManager::GetInstance()->FindImage(L"FireMarioLeft");
		else hMemDC = CBitmapManager::GetInstance()->FindImage(L"FireMarioRight");
		break;
	}

	Mario(hDC, hMemDC, m_tInfo, m_tRect, m_bFacingLeft, m_eActionStatus, m_ePlayerStatus, m_iAnimationTime, { CScrollManager::GetInstance()->GetScrollX(), 0 });
	if (g_bDevmode)
	{
		TCHAR	temp[30];
		swprintf(temp, sizeof(temp), L"fTime: %d", m_iAnimationTime);
		TextOut(hDC, 0, 80, temp, lstrlenW(temp));
		Hitbox(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
	}
}

void CMHPlayer::Release()
{
}

void CMHPlayer::OnCollision(CObject* _op)
{
	if (_op->GetID() == OBJ_ITEM)
	{
		ITEMTYPE is = dynamic_cast<CItem*>(_op)->GetItemType();
		switch (is)
		{
		case ITEM_NONE:
			break;
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

	if (_op->GetID() == OBJ_MONSTER)
	{
		//MONSTER의 위와 플레이어의 아래충돌
		if (m_tRect.bottom > _op->GetRECT()->top && m_tRect.top < _op->GetRECT()->top)
		{
			m_tInfo.fY = _op->GetRECT()->top - m_tInfo.fCY * 0.5f + 1.f;
			m_fVelocityY = 0.f;
			m_fTime = 0.f;
			m_bIsGround = true;
		}
		//Box의 아래와 플레이어의 윗충돌
		else
		{
			m_iHp -= 1;
			if(m_iHp < 0) OnDead();
		}
	}
}

void CMHPlayer::OnDead()
{
	m_bIsDead = true;
}

void CMHPlayer::Jump()
{
	float fY(0.f);

	if (!m_bIsGround)
	{
		m_tInfo.fY -= (int)(m_fJumpPower * sinf(45.f) * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.5f;
  		m_fTime += 0.2f;
	}
}

void CMHPlayer::KeyInput()
{
	float	fY(0.f);
	//m_tDir = { 0, 0 };
  	if(m_bIsGround) m_eActionStatus = AS_STOP;

	if (CKeyManager::GetInstance()->KeyPressing(VK_LEFT))
	{
		m_tDir.SetX(-1);
		m_eActionStatus = AS_MOVE;
		m_bFacingLeft = true;
	}

	if (CKeyManager::GetInstance()->KeyPressing(VK_RIGHT))
	{
		m_tDir.SetX(1);
		m_eActionStatus = AS_MOVE;
		m_bFacingLeft = false;
	}

	if (CKeyManager::GetInstance()->KeyDown(VK_SPACE))
	{
		if (m_bIsGround)
		{
			//m_tInfo.fY = 100.f;
       		m_tDir.y = -2;
			m_fVelocityY = -10;
			//m_eActionStatus = AS_JUMP;
			m_bIsGround = false;
			m_fTime = 0.f;
		}
	}

	if (CKeyManager::GetInstance()->KeyPressing('A'))
	{
		if (m_ePlayerStatus == PS_FIRE)
		{
			if (m_ullLastFire + m_ullFireDelay < GetTickCount64())
			{
				Fire();
				m_ullLastFire = GetTickCount64();
			}
			
		}
	}

	if (CKeyManager::GetInstance()->KeyUp(VK_UP))
	{
		m_tInfo.fY = 0.f;
		m_bIsGround = false;
	}

	if (CKeyManager::GetInstance()->KeyDown('O') && g_bDevmode)
	{
		m_tInfo.fY = WINCY / 2;
		
	}
	if (CKeyManager::GetInstance()->KeyUp(VK_DOWN) && g_bDevmode)
	{
		m_bIsGround = false;
		if (m_ePlayerStatus == PS_SMALL)
		{
			OnMushroom();
		}
		else
		{
			OnFlower();
		}
		
	}
}

void CMHPlayer::ScrollOffset()
{

	/*int		iOffSetX = WINCX >> 1;

	int		iScrollX = (int)CScrollManager::GetInstance()->GetScrollX();

	if (iOffSetX > m_tInfo.fX + iScrollX)
		CScrollManager::GetInstance()->SetScrollX(m_fSpeed);

	if (iOffSetX < m_tInfo.fX + iScrollX)
		CScrollManager::GetInstance()->SetScrollX(-m_fSpeed);*/


	//int		iOffSetminX = -100;
	int		iOffSetmaxX = 500;

	int		iScrollX = (int)CScrollManager::GetInstance()->GetScrollX();

	/*if (iOffSetminX > m_tInfo.fX + iScrollX)
		CScrollManager::GetInstance()->SetScrollX(m_fSpeed);*/

	if (iOffSetmaxX < m_tInfo.fX + iScrollX)
		CScrollManager::GetInstance()->SetScrollX(-m_fSpeed);
}

bool CMHPlayer::CheckOnGround()
{
	for (auto& b : CObjectManager::GetInstance()->GetList())
	{
		if (CCollisionManager::CheckRect(this, b)) return true;
	}
	
	return false;
}

void CMHPlayer::OnMushroom()
{
	if (m_ePlayerStatus == PS_SMALL)
	{
		m_ePlayerStatus = PS_BIG;
		m_tInfo.fCX = 52.f;
		m_tInfo.fCY = 70.f;
	}
}

void CMHPlayer::OnFlower()
{
	if (m_ePlayerStatus == PS_BIG || m_ePlayerStatus == PS_SMALL)
	{
		m_ePlayerStatus = PS_FIRE;
		m_tInfo.fCX = 52.f;
		m_tInfo.fCY = 70.f;
	}
}

void CMHPlayer::Fire()
{
	if (m_ePlayerStatus == PS_FIRE)
	{
		if(!m_bFacingLeft)
			CObjectManager::GetInstance()->Add_Object(OBJ_PROJECTILE, CAbstractFactory<CProjectile>::Create(m_tInfo.fX + CScrollManager::GetInstance()->GetScrollX(), m_tInfo.fY, m_eOID, 0.f));
		else 
			CObjectManager::GetInstance()->Add_Object(OBJ_PROJECTILE, CAbstractFactory<CProjectile>::Create(m_tInfo.fX + CScrollManager::GetInstance()->GetScrollX(), m_tInfo.fY, m_eOID, 180.f));
	}
}
