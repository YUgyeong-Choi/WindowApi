#include "pch.h"
#include "CPlayer.h"
#include "CKeyManager.h"
#include "CCollisionManager.h"
#include "CScrollManager.h"

CPlayer::CPlayer(): m_bPlayerStatus(PS_END)
{
}

void CPlayer::Initialize()
{
	m_tInfo = { 100, 10, 30.f, 30.f };
	m_fSpeed = 5.f;
	m_fJumpPower = 20.f;
	m_bActionStatus = AS_FALL;
	m_fFallSpeed = 10.f;
}

int CPlayer::Update()
{
	if (m_bActionStatus == AS_FALL) {
		m_tInfo.fY += m_fFallSpeed;
	}


	__super::UpdateRect();
	return OBJ_NOEVENT;
}

void CPlayer::LateUpdate()
{
	KeyInput();
	Jump();
	ScrollOffset();
}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
	if (g_bDevmode) Hitbox(hDC, m_tRect);
}

void CPlayer::Release()
{
}

void CPlayer::OnCollision(CObject* _op)
{
}

void CPlayer::OnDead()
{
}

void CPlayer::Jump()
{
	if (m_bActionStatus == AS_JUMP)
	{
		m_tInfo.fY -= (m_fJumpPower * sinf(45.f) * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.5f;
		m_fTime += 0.2f;
		if (m_tInfo.fY > 500) { //높은 곳에서 뛰어내리면 fY값이 네모의 fY값에 없어서 충돌 처리가 안되서 그거 방지
			m_tInfo.fY += (m_fJumpPower * sinf(45.f) * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.5f;
			SetActionStatus(AS_FALL);
		}
	}

	if (m_bActionStatus == AS_STOP) {
		m_fTime = 0.f;
	}
	
}

void CPlayer::KeyInput()
{
	float	fY(0.f);

	if (CKeyManager::GetInstance()->KeyPressing(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
		if (m_bActionStatus != AS_JUMP) {
			SetActionStatus(AS_FALL);
		}
	}

	if (CKeyManager::GetInstance()->KeyPressing(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
		if (m_bActionStatus != AS_JUMP) {
			SetActionStatus(AS_FALL);
		}
	}

	if (CKeyManager::GetInstance()->KeyDown(VK_SPACE))
	{
		if (m_bActionStatus == AS_STOP) {
			SetActionStatus(AS_JUMP);
		}
	}
}

void CPlayer::ScrollOffset()
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
