#include "pch.h"
#include "CPlayerYK.h"
#include "CKeyManager.h"
#include "CCollisionManager.h"
#include "CScrollManager.h"
#include "CBitmapManager.h"

CPlayerYK::CPlayerYK() : m_bPlayerStatus(PS_END), friction(0)
{
}

void CPlayerYK::Initialize()
{
	m_tInfo = { 100, 10, 40.f, 40.f };
	m_fSpeed = 10.f;
	m_fJumpPower = 20.f;
	m_fFallSpeed = 5.f;
	m_fTime = 0.f;
	m_bIsGround = false;
	m_tDir = { 0 , 1 };
	friction = 0.8f;
}

int CPlayerYK::Update()
{
	m_tInfo.fX += m_tDir.GetX() * m_fSpeed;
	m_tInfo.fY += m_tDir.GetY() * m_fSpeed;
	m_fTime += 0.2f;
	KeyInput();
	__super::UpdateRect();
	return OBJ_NOEVENT;
}

void CPlayerYK::LateUpdate()
{
	if (!m_bIsGround && m_fTime >= 2.f) m_tDir.SetY(1);
	if (m_bIsGround) {
		m_tDir.SetX(m_tDir.GetX() * friction);
	}
	ScrollOffset();
}

void CPlayerYK::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
	
	if (g_bDevmode) Hitbox(hDC, m_tRect);
}

void CPlayerYK::Release()
{
}

void CPlayerYK::OnCollision(CObject* _op)
{
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
		m_eAction = AS_MOVE_LEFT;
	}

	if (CKeyManager::GetInstance()->KeyPressing(VK_RIGHT))
	{
		m_tDir.SetX(1);
		m_eAction = AS_MOVE_RIGHT;
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
