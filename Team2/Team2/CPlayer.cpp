#include "pch.h"
#include "CPlayer.h"
#include "CKeyManager.h"

CPlayer::CPlayer() : m_bJump(false), m_fJumpPower(0.f), m_fTime(0.f)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo = { 100.f, WINCY / 2.f, 100.f, 100.f };
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
}

void CPlayer::Render(HDC _hDC)
{
	Rectangle(_hDC, m_tRect.left , m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CPlayer::Release()
{
}

void CPlayer::Key_Input()
{
	if (CKeyManager::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
	}

	if (CKeyManager::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;

	}

	if (CKeyManager::Get_Instance()->Key_Down(VK_SPACE))
	{
		m_bJump = true;
	}
}

void CPlayer::Jumping()
{
	if (m_bJump)
	{
		m_tInfo.fY -= (m_fJumpPower * sinf(90.f) * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.5f;
		m_fTime += 0.2f;
	}
}
