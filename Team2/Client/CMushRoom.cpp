#include "pch.h"
#include "CMushRoom.h"
#include "CScrollManager.h"
#include "CObjectManager.h"
#include "CCollisionManager.h"
#include "CPlayerDH.h"
#include "CBitmapManager.h"

CMushRoom::CMushRoom()
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
	m_tDir = { 1 , 1 };
}

int CMushRoom::Update()
{
	if (m_bIsDead)
		return OBJ_DEAD;

	if (m_fTime >= 20) {
		m_tDir.SetX(m_tDir.GetX()*-1);
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

void CMushRoom::OnCollision(CObject* _op)
{
	if (OBJ_PLAYER == _op->GetOBJID()) {
		SetIsDead(true);
	}

	if (_op->GetOBJID() == OBJ_BLOCK) {
		m_tDir.SetX(m_tDir.GetX() * -1);
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
