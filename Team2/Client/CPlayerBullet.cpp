#include "pch.h"
#include "CPlayerBullet.h"
#include "CScrollManager.h"'
#include "CObjectManager.h"

CPlayerBullet::CPlayerBullet()
{
}

void CPlayerBullet::Initialize()
{
	m_tInfo.fCX = 15.f;
	m_tInfo.fCY = 15.f;
	m_fSpeed = 5.f;
	m_fJumpPower = 10.f;
}

int CPlayerBullet::Update()
{
	if (true == m_bIsDead)
		return OBJ_DEAD;

	//m_tInfo.fX += m_fJumpPower * cosf(m_fAngle) * m_fTime; // �÷��̾� ���⿡���� ��
	//m_tInfo.fY -= (m_fJumpPower * sinf(45.f) * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.5f;
	//m_fTime += 0.1f;

	ACTIONSTATUS as = CObjectManager::GetInstance()->GetPlayer()->GetActionStatus();
	if (as == AS_MOVE_LEFT) {
		m_tInfo.fX -= 10.f;
	}
	else {
		m_tInfo.fX += 10.f;
	}
	

	CObject::UpdateRect();

	return OBJ_NOEVENT;
}

void CPlayerBullet::LateUpdate()
{

}

void CPlayerBullet::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect, { 0.f, 0.f }, 0.f, 0.f, RGB(255, 0, 0));
}

void CPlayerBullet::Release()
{
}

void CPlayerBullet::OnCollision(CObject* _op)
{
}

void CPlayerBullet::OnDead()
{
}
