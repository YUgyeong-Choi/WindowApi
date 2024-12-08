#include "pch.h"
#include "CPlayerMH.h"
#include "CKeyManager.h"
#include "CCollisionManager.h"
#include "CScrollManager.h"
#include "CLineManager.h"
#include "CBitmapManager.h"

CPlayerMH::CPlayerMH() : m_fJumpTime(0.f), m_ePlayerStatus(PS_SMALL)
{
}

void CPlayerMH::Initialize()
{
	m_tInfo = { WINCX * 0.5f, WINCY * 0.0f, 40.f, 40.f };
	m_fSpeed = 10.f;
	m_fJumpPower = 20.f;
	
	m_bIsGround = false;
	m_bIsJumping = false;
	m_fJumpTime = m_fJumpPower * sinf(45.f) / 9.8f;

	CBitmapManager::GetInstance()->InsertBitmap(RESORUCEPATH L"Player/SmallMario/SmallMarioLeft.bmp", L"Player");
}

int CPlayerMH::Update()
{
	KeyInput();
	__super::UpdateRect();
	return OBJ_NOEVENT;
}

void CPlayerMH::LateUpdate()
{
	if (!m_pTarget)
		m_tInfo.fY += m_fSpeed;
	if (m_pTarget)
	{
		if ((m_pTarget->GetRECT()->left < m_tRect.right) || (m_pTarget->GetRECT()->right > m_tRect.left))
		{
			m_pTarget = nullptr;
		}
	}
	
	Jump();
	ScrollOffset();
	if (m_tInfo.fY >= 2000.f)
	{
		m_tInfo.fY = 0.f;
		m_bIsJumping = false;
	}

}

void CPlayerMH::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollManager::GetInstance()->GetScrollX();

	HDC		hMemDC = CBitmapManager::GetInstance()->FindImage(L"Player");
	//Rectangle(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0}, 0, 0);
	SmallMario(hDC, hMemDC, m_tInfo, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
	if (g_bDevmode) Hitbox(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
}

void CPlayerMH::Release()
{
}

void CPlayerMH::OnCollision(CObject* _op)
{
	if (_op->GetOBJID() == OBJ_NONE)
	{
		m_tInfo.fY = _op->GetRECT()->top - m_tInfo.fCX * 0.5f + 1.f;
		m_bIsJumping = false;
		m_fTime = 0.f;
		m_pTarget = _op;
	}
}

void CPlayerMH::OnDead()
{
}

void CPlayerMH::Jump()
{
	float fY(0.f);

	if (m_bIsJumping && !m_pTarget)
	{
		m_tInfo.fY -= (int)(m_fJumpPower * sinf(45.f) * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.5f;
		m_fTime += 0.2f;
		if (m_fTime >= m_fJumpTime)
		{
		}
		if (m_pTarget)
		{
			m_fTime = 0.f;
			m_bIsJumping = false;
		}
	}
}

void CPlayerMH::KeyInput()
{
	float	fY(0.f);

	if (CKeyManager::GetInstance()->KeyPressing(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
	}

	if (CKeyManager::GetInstance()->KeyPressing(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
	}

	if (CKeyManager::GetInstance()->KeyUp(VK_SPACE))
	{

	}

	if (CKeyManager::GetInstance()->KeyUp(VK_UP))
	{
		m_tInfo.fY = 0.f;
	}
	if (CKeyManager::GetInstance()->KeyUp(VK_DOWN))
	{
	}
}

void CPlayerMH::ScrollOffset()
{

	/*int		iOffSetX = WINCX >> 1;

	int		iScrollX = (int)CScrollManager::GetInstance()->GetScrollX();

	if (iOffSetX > m_tInfo.fX + iScrollX)
		CScrollManager::GetInstance()->SetScrollX(m_fSpeed);

	if (iOffSetX < m_tInfo.fX + iScrollX)
		CScrollManager::GetInstance()->SetScrollX(-m_fSpeed);*/


	int		iOffSetminX = 300;
	int		iOffSetmaxX = 500;

	int		iScrollX = (int)CScrollManager::GetInstance()->GetScrollX();

	if (iOffSetminX > m_tInfo.fX + iScrollX)
		CScrollManager::GetInstance()->SetScrollX(m_fSpeed);

	if (iOffSetmaxX < m_tInfo.fX + iScrollX)
		CScrollManager::GetInstance()->SetScrollX(-m_fSpeed);
}
