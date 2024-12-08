#include "pch.h"
#include "CMushRoom.h"
#include "CScrollManager.h"
#include "CObjectManager.h"
#include "CCollisionManager.h"
#include "CPlayerDH.h"

CMushRoom::CMushRoom():m_iAiDir(0)
{
	m_eItemType = ITEM_MUSHROOM;
}

CMushRoom::~CMushRoom()
{
}

void CMushRoom::Initialize()
{
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
	m_fSpeed = 5.f;
	m_bIsGround = false;
	m_tDir = { 0 , 1 };
	m_iAiDir = 1;
}

int CMushRoom::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;

	if (m_fTime >= 50) {
		m_tDir.SetX(m_iAiDir);
		m_iAiDir *= -1;
		m_fTime = 0.f;
	}

	m_tInfo.fX += m_tDir.GetX() * m_fSpeed;
	m_tInfo.fY += m_tDir.GetY() * m_fSpeed;
	m_fTime += 0.2f;
	__super::UpdateRect();

	return OBJ_NOEVENT;
}

void CMushRoom::LateUpdate()
{
	if (!m_bIsGround && m_fTime >= 2.f) m_tDir.SetY(1);
}

void CMushRoom::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
	if (g_bDevmode) Hitbox(hDC, m_tRect);
}

void CMushRoom::OnCollision(CObject* _op)
{
	if (OBJ_PLAYER == _op->GetOBJID()) {
		SetIsDead(true);
	}

	if (OBJ_BLOCK == _op->GetOBJID()) {
		m_tDir.SetY(-1);
		m_bIsGround = false;
		m_fTime = 0.f;
	}

	//if (OBJ_PLAYER == _op->GetOBJID())
	//{
	//	
	//	static_cast<CPlayerDH*>(_op)->SetPlayerState(PS_BIG);
	//	// 크기 수정 필요
	//	(_op)->SetSize(100.f, 100.f);

	//	SetIsDead(true);
	//}
}

void CMushRoom::Move()
{
}

bool CMushRoom::CheckOnGround()
{
	for (auto& b : CObjectManager::GetInstance()->GetList())
	{
		if (CCollisionManager::CheckRect(this, b)) return true;
	}

	return false;
}
