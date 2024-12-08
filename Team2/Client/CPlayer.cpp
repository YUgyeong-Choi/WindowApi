#include "pch.h"
#include "CPlayer.h"
#include "CKeyManager.h"
#include "CCollisionManager.h"
#include "CScrollManager.h"
#include "CBox.h"

CPlayer::CPlayer()
{
	
}

void CPlayer::Initialize()
{
	m_tInfo = { WINCX * 0.5f, WINCY * 0.5f, 40.f, 40.f };
	m_fSpeed = 5.f;
	m_fJumpPower = 10.f;	
	m_fCurrentGravity = m_fGravity;
}

int CPlayer::Update()
{
	KeyInput();

	switch (m_eAction)
	{
	case AS_JUMP:
	{
		// 점프 시간 별 상태.
		if (m_fTime < 2.0f)
		{			
			// 점프 시간하고나서 2초까지.
			m_tInfo.fY -= (m_fJumpPower * sinf(90.f * (PI / 180.f)) * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.5f;
		}
		else
		{
			// 2초 후엔 중력 속도만큼 떨어지게 함.
			m_tInfo.fY += m_fCurrentGravity;
		}		

		m_fTime += 0.05f;
		break;
	}
	}

	// 점프 상태가 아닐 경우에만 중력에 영향을 받는다.
	if (m_eAction != AS_JUMP)
	{
		m_fTime = 0.0f;
		m_tInfo.fY += m_fCurrentGravity;
	}
		
	__super::UpdateRect();
	return OBJ_NOEVENT;
}

void CPlayer::LateUpdate()
{	
	//Jump();
	ScrollOffset();
}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect, {CScrollManager::GetInstance()->GetScrollX(), 0});
	if (g_bDevmode) Hitbox(hDC, m_tRect);
}

void CPlayer::Release()
{
}

void CPlayer::OnCollision(CObject* _op)
{	
	switch (_op->GetOBJID())
	{
	case OBJ_BOX:
	{		
		// 각도를 기반으로 여러 충돌 판정을 구현함.
		float degree = GetDegreeAngle(_op->GetINFO());

		CBox* block = static_cast<CBox*>(_op);
		
		if ((degree > 0.f && degree <= 180.f))
		{
			// 위쪽 충돌.
			if (degree >= 150.f && degree <= 180.f)
			{
				// 위쪽 왼쪽
				m_tInfo.fX = _op->GetRECT()->right + (m_tInfo.fCX * 0.5f);
			}

			if (degree <= 4.f && degree >= 45.f)
			{
				// 위쪽 오른쪽
				m_tInfo.fX = _op->GetRECT()->left - (m_tInfo.fCX * 0.5f);
			}

			// 벽돌 위에서 충돌.
			// 지형에 닿으면 플레이어 상태 변경.
			// 점프 시간 초기화
			if (degree >= 45.f && degree <= 125.f)
			{
				m_fTime = 0.f;
				m_eAction = ACTIONSTATUS::AS_STOP;
				m_tInfo.fY = _op->GetRECT()->top - (m_tInfo.fCY * 0.55f);
			}			
		}

		if (degree < 0.f && degree >= -180.f)
		{
			// 아래쪽 충돌.
			if (degree <= -4.f && degree >= -45.f)
			{
				// 아래쪽 왼쪽
				m_tInfo.fX = _op->GetRECT()->left - (m_tInfo.fCX * 0.5f);
			}

			if (degree < -135.f && degree >= -180.f)
			{
				// 아래쪽 오른쪽
				m_tInfo.fX = _op->GetRECT()->right + (m_tInfo.fCX * 0.5f);
			}

			// 플레이어가 벽돌 아래에서 못 올라오게 막음.
			m_fTime = 0.f;
			m_eAction = ACTIONSTATUS::AS_STOP;

			// 블럭 이벤트 호출.
			block->OnBlockEvent();
		}
	}
		break;
	}	
}

void CPlayer::OnDead()
{
}

void CPlayer::Jump()
{
	float	fY(0.f);

	bool	bLineCol = CCollisionManager::CollisionLine(m_tInfo.fX, &fY);

	if (m_eAction == ACTIONSTATUS::AS_JUMP)
	{
		m_tInfo.fY -= (m_fJumpPower * sinf(45.f) * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.5f;
		m_fTime += 0.2f;

		if (bLineCol && (fY < m_tInfo.fY))
		{
			m_eAction = ACTIONSTATUS::AS_STOP;
			m_fTime = 0.f;
			m_tInfo.fY = fY;
		}
	}
	else if (bLineCol)
	{
		m_tInfo.fY = fY;
	}
}

void CPlayer::KeyInput()
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

	if (CKeyManager::GetInstance()->KeyDown(VK_SPACE))
	{
		m_eAction = ACTIONSTATUS::AS_JUMP;
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
