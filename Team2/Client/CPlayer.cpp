#include "pch.h"
#include "CPlayer.h"
#include "CKeyManager.h"
#include "CCollisionManager.h"
#include "CScrollManager.h"

CPlayer::CPlayer(): m_bPlayerStatus(PS_END), m_bIsGround(false)
{
}

void CPlayer::Initialize()
{
	m_tInfo = { WINCX * 0.5f, WINCY * 0.5f, 100.f, 100.f };
	m_fSpeed = 10.f;
	m_fJumpPower = 20.f;
}

int CPlayer::Update()
{
	KeyInput();
	__super::UpdateRect();
	return OBJ_NOEVENT;
}

void CPlayer::LateUpdate()
{
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
	if (_op->GetOID() == OBJ_ITEM) {
		
		if (m_tInfo.fY > _op->GetINFO().fY) {
			_op->SetIsDead(true);
		}
	}
	else if (_op->GetOID() == OBJ_RECT) {
		if (m_tInfo.fY < _op->GetINFO().fY) {
			m_tInfo.fY = _op->GetINFO().fY + _op->GetINFO().fCY * 0.5f;
			m_bIsGround = true;
		}
		else {
			_op->SetIsDead(true);
		}
	}
}

void CPlayer::OnDead()
{
}

void CPlayer::Jump()
{
	if (!m_bIsGround) {
		float	fY(0.f);

		bool	bLineCol = CCollisionManager::CollisionLine(m_tInfo.fX, &fY);

		if (GetActionStatus() == AS_JUMP)
		{
			m_tInfo.fY -= (m_fJumpPower * sinf(45.f) * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.5f;
			m_fTime += 0.2f;

			if (bLineCol && (fY < m_tInfo.fY))
			{
				SetActionStatus(AS_END);
				m_fTime = 0.f;
				m_tInfo.fY = fY;
			}
		}
		else if (bLineCol)
		{
			if (fY > m_tInfo.fY)
				m_tInfo.fY += m_fSpeed;
			else
				m_tInfo.fY = fY;
		}
	}

}

void CPlayer::KeyInput()
{
	float	fY(0.f);

	if (CKeyManager::GetInstance()->KeyPressing(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
	}

	if (CKeyManager::GetInstance()->KeyDown(VK_SPACE))
	{
		SetActionStatus(AS_JUMP);
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
