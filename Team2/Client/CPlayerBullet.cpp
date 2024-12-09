#include "pch.h"
#include "CPlayerBullet.h"
#include "CScrollManager.h"'
#include "CObjectManager.h"

CPlayerBullet::CPlayerBullet() :m_dir(false)
{
}

void CPlayerBullet::Initialize()
{
	m_tInfo.fCX = 15.f;
	m_tInfo.fCY = 15.f;
	m_fSpeed = 5.f;
	m_fJumpPower = 10.f; 
	m_bIsDead = false;
	m_dir = CObjectManager::GetInstance()->GetPlayer()->GetDir();

}

int CPlayerBullet::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;

	//m_tInfo.fX += m_fJumpPower * cosf(m_fAngle) * m_fTime; // 플레이어 방향에따라서 쏨
	//m_tInfo.fY -= (m_fJumpPower * sinf(45.f) * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.5f;
	//m_fTime += 0.1f;
	if (m_dir) {
		m_tInfo.fX -= m_fSpeed;
	}
	else {
		m_tInfo.fX += m_fSpeed;
	}

	CObject::UpdateRect();

	return OBJ_NOEVENT;
}

void CPlayerBullet::LateUpdate()
{

}

void CPlayerBullet::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0.f}, 0.f, 0.f, RGB(255, 0, 0));
}

void CPlayerBullet::Release()
{
}

void CPlayerBullet::OnCollision(CObject* _op)
{
	if (_op->GetOBJID() == OBJ_BLOCK) {
		SetIsDead(true);
	}

	if (_op->GetOBJID() == OBJ_MONSTER) {
		SetIsDead(true);
	}
}

void CPlayerBullet::OnDead()
{
}
