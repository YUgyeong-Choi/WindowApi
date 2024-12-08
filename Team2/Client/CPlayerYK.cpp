#include "pch.h"
#include "CPlayerYK.h"
#include "CKeyManager.h"
#include "CCollisionManager.h"
#include "CScrollManager.h"
#include "CBitmapManager.h"

CPlayerYK::CPlayerYK() : m_bPlayerStatus(PS_END)
{
}

void CPlayerYK::Initialize()
{
	m_tInfo = { 100, 10, 40.f, 40.f };
	m_fSpeed = 5.f;
	m_fJumpPower = 20.f;
	m_eAction = AS_FALL;
	m_fFallSpeed = 5.f;
	CBitmapManager::GetInstance()->InsertBitmap(RESORUCEPATH L"Player/SmallMario/SmallMarioLeft.bmp", L"Player");
	CBitmapManager::GetInstance()->InsertBitmap(RESORUCEPATH L"Player/BigMario/BigMarioLeft.bmp", L"Player");
}

int CPlayerYK::Update()
{
	if (m_eAction == AS_FALL) {
		m_tInfo.fY += m_fFallSpeed;
	}

	KeyInput();
	__super::UpdateRect();
	return OBJ_NOEVENT;
}

void CPlayerYK::LateUpdate()
{
	Jump();
	ScrollOffset();
}

void CPlayerYK::Render(HDC hDC)
{
	HDC		hMemDC = CBitmapManager::GetInstance()->FindImage(L"Player");

	if (m_bPlayerStatus == PS_SMALL) {
		SmallMario(hDC, hMemDC, m_tInfo, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
	}
	else {
		//static void BigMario(HDC hDC, HDC hMemDC, INFO m_tInfo, RECT m_tRect, bool left, ACTIONSTATUS as, PLAYERSTATUS ps, int& t, Vector<float> offset = { 0, 0 })
		//BigMario(hDC, hMemDC, m_tInfo, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
	}
	//Rectangle(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0}, 0, 0);
	
	if (g_bDevmode) Hitbox(hDC, m_tRect);
}

void CPlayerYK::Release()
{
}

void CPlayerYK::OnCollision(CObject* _op)
{
	switch (_op->GetOBJID())
	{
	case OBJ_BLOCK:
		//상 충돌
		if (_op->GetINFO().fY > m_tInfo.fY) {
			SetActionStatus(AS_STOP);
			SetFallSpeed(3.f);
			SetPos(m_tInfo.fX, _op->GetINFO().fY - _op->GetINFO().fCY*0.5 - m_tInfo.fCY*0.5f);
		}

		// 하 충돌
		if (_op->GetINFO().fY < m_tInfo.fY - m_tInfo.fCY * 0.5f) {
			SetActionStatus(AS_FALL);
			SetFallSpeed(50.f);
		}
		
		break;
	default:
		break;
	}
}

void CPlayerYK::OnDead()
{
}

void CPlayerYK::Jump()
{
	if (m_eAction == AS_JUMP)
	{
		m_tInfo.fY -= (m_fJumpPower * sinf(45.f) * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.5f;
		m_fTime += 0.2f;
		if (m_tInfo.fY > 550) { //높은 곳에서 뛰어내리면 fY값이 네모의 fY값에 없어서 충돌 처리가 안되서 그거 방지
			m_tInfo.fY += (m_fJumpPower * sinf(45.f) * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.5f;
			SetActionStatus(AS_FALL);
		}
	}

	if (m_eAction == AS_STOP) {
		m_fTime = 0.f;
	}

}

void CPlayerYK::KeyInput()
{

	if (CKeyManager::GetInstance()->KeyPressing(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;

		if (CKeyManager::GetInstance()->KeyDown(VK_SPACE))
		{
			if (m_eAction == AS_STOP) {
				SetActionStatus(AS_JUMP);
			}
		}

		if (m_eAction != AS_JUMP) {
			SetActionStatus(AS_FALL);
		}

	}

	if (CKeyManager::GetInstance()->KeyPressing(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;

		if (CKeyManager::GetInstance()->KeyDown(VK_SPACE))
		{
			if (m_eAction == AS_STOP) {
				SetActionStatus(AS_JUMP);
			}
		}

		if (m_eAction != AS_JUMP) {
			SetActionStatus(AS_FALL);
		}
	}

	if (CKeyManager::GetInstance()->KeyDown(VK_SPACE))
	{
		if (m_eAction == AS_STOP) {
			SetActionStatus(AS_JUMP);
		}
	}
}

void CPlayerYK::ScrollOffset()
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
