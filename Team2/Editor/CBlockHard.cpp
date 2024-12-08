#include "pch.h"
#include "CBlockHard.h"

CBlockHard::CBlockHard()
{
}

CBlockHard::~CBlockHard()
{
}

void CBlockHard::Initialize()
{
    m_tInfo = { m_tInfo.fX, m_tInfo.fY, 50.f, 50.f };
   
}

int CBlockHard::Update()
{
	if (m_bIsDead == true)
	{
		return OBJ_DEAD;
	}

	__super::UpdateRect();
	return OBJ_NOEVENT;
}

void CBlockHard::LateUpdate()
{
}

void CBlockHard::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
	if (g_bDevmode) Hitbox(hDC, m_tRect);
}

void CBlockHard::Release()
{
}

void CBlockHard::OnCollision(CObject* _op)
{
}
