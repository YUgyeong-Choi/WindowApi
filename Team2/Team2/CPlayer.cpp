#include "pch.h"
#include "CPlayer.h"
#include "CKeyManager.h"
#include "CScrollManager.h"
#include "CLineManager.h"

CPlayer::CPlayer() : m_bJump(false), m_fJumpPower(0.f), m_fTime(0.1f)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo = { 100.f, 200.f, 70.f, 70.f };
	m_fSpeed = 10.f;
	m_fJumpPower = 20.f;
}

int CPlayer::Update()
{
	Key_Input();
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
	Jumping();
	Offset();
}

void CPlayer::Render(HDC _hDC)
{
	int		iScrollX = (int)CScrollManager::Get_Instance()->Get_ScrollX();
	Rectangle(_hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
}

void CPlayer::Release()
{
}

void CPlayer::Key_Input()
{
	float	fY(0.f);
	if (CKeyManager::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
		CLineManager::Get_Instance()->Collision_Line(m_tInfo.fX, &fY);
		m_tInfo.fY = fY;
	}

	if (CKeyManager::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
		CLineManager::Get_Instance()->Collision_Line(m_tInfo.fX, &fY);
		m_tInfo.fY = fY;
	}

	if (CKeyManager::Get_Instance()->Key_Down(VK_SPACE))
	{
		m_bJump = true;

	}

}

void CPlayer::Jumping()
{
	float	fY(0.f);
	bool	bLineCol = CLineManager::Get_Instance()->Collision_Line(m_tInfo.fX, &fY);

	if (m_bJump)
	{
		m_tInfo.fY -= (m_fJumpPower * sinf(90.f) * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.5f;
		m_fTime += 0.2f;

		if (bLineCol && (fY < m_tInfo.fY))
		{
			m_bJump = false;
			m_fTime = 0.f;
			m_tInfo.fY = fY;
		}
	}
}

void CPlayer::Offset()
{
	/*int		iOffSetX = WINCX >> 1;

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	if (iOffSetX > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	if (iOffSetX < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);*/

	int		iOffSetminX = 100;
	int		iOffSetmaxX = 700;

	int		iScrollX = (int)CScrollManager::Get_Instance()->Get_ScrollX();

	if (iOffSetminX > m_tInfo.fX + iScrollX)
		CScrollManager::Get_Instance()->Set_ScrollX(m_fSpeed);

	if (iOffSetmaxX < m_tInfo.fX + iScrollX)
		CScrollManager::Get_Instance()->Set_ScrollX(-m_fSpeed);


}
