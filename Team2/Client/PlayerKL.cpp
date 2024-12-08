#include "pch.h"
#include "CPlayerKL.h"
#include "CKeyManager.h"
#include "CCollisionManager.h"
#include "CScrollManager.h"

CPlayerKL::CPlayerKL() : m_ePstatus(PS_SMALL), m_bCollision(false)
{
}

void CPlayerKL::Initialize()
{
	m_tInfo = { 300, WINCY * 0.5f, 75.f, 75.f };
	m_fSpeed = 10.f;
	m_fJumpPower = 20.f;
}

int CPlayerKL::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;



	KeyInput();

	__super::UpdateRect();
	return OBJ_NOEVENT;
}

void CPlayerKL::LateUpdate()
{

	SelectAction();
	//Jumping();

	if (!m_bCollision)
		SetActionStatus(AS_FALL);

	ScrollOffset();
}

void CPlayerKL::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
	if (g_bDevmode) Hitbox(hDC, m_tRect);
}

void CPlayerKL::Release()
{
}

void CPlayerKL::OnCollision(CObject* _op)
{

	if (OBJ_MONSTER == _op->GetOBJID())
	{
		SetActionStatus(AS_STOP);
		if (m_tInfo.fY > _op->GetINFO().fY)
			SetIsDead(true);
		m_bCollision = false;

	}
	if (OBJ_BOX == _op->GetOBJID())
	{
		if (m_tInfo.fY < _op->GetINFO().fY)
		{
			SetActionStatus(AS_STOP);
			m_fTime = 0.f;
			m_tInfo.fY = _op->GetINFO().fY - _op->GetINFO().fCY * 0.5f - GetINFO().fCY * 0.5f;
			m_bCollision = true;
		}
		else
		{
			SetActionStatus(AS_FALL);
			m_bCollision = false;
		}
	}


}

void CPlayerKL::OnDead()
{
}

void CPlayerKL::SelectAction()
{

	switch (m_eAction)
	{
	case AS_STOP:

		m_fTime = 0.f;
		break;
		//case AS_MOVE_LEFT:
		//	m_tInfo.fX -= m_fSpeed;
		//
		//	break;
		//case AS_MOVE_RIGHT:
		//	m_tInfo.fX += m_fSpeed;
		//	break;
	case AS_FALL:
		m_tInfo.fY += m_fSpeed;

		break;
	case AS_JUMP:
		m_tInfo.fY -= (m_fJumpPower * sinf(PI / 2) * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.5f;
		m_fTime += 0.2f;

		break;
	case AS_END:
		break;
	default:
		break;
	}
}





void CPlayerKL::Jumping()
{
	float	fY(0.f);

	bool	bLineCol = CCollisionManager::CollisionLine(m_tInfo.fX, &fY);

	if (AS_JUMP == m_eAction)
	{
		m_tInfo.fY -= (m_fJumpPower * sinf(PI / 2) * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.5f;
		m_fTime += 0.2f;

		if (bLineCol && (fY < m_tInfo.fY))
		{
			SetActionStatus(AS_STOP);
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
void CPlayerKL::SelectStatus()
{
}





void CPlayerKL::KeyInput()
{
	float	fY(0.f);

	if (CKeyManager::GetInstance()->KeyPressing(VK_LEFT))
	{
		if (AS_JUMP != m_eAction)
			SetActionStatus(AS_FALL);
		//SetStatus(AS_MOVE_LEFT);
		m_tInfo.fX -= m_fSpeed;

	}

	if (CKeyManager::GetInstance()->KeyPressing(VK_RIGHT))
	{
		if (AS_JUMP != m_eAction)
			SetActionStatus(AS_FALL);

		//SetStatus(AS_MOVE_RIGHT);
		m_tInfo.fX += m_fSpeed;

	}

	if (CKeyManager::GetInstance()->KeyPressing(VK_SPACE))
	{
		SetActionStatus(AS_JUMP);
	}

	if (CKeyManager::GetInstance()->KeyPressing('S'))
	{
		SetActionStatus(AS_STOP);

	}
}

void CPlayerKL::CreateBullet()
{
}

void CPlayerKL::ScrollOffset()
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
