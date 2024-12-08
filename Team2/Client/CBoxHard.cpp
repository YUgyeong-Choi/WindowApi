#include "pch.h"
#include "CBoxHard.h"

CBoxHard::CBoxHard()
{
}

CBoxHard::~CBoxHard()
{
}

void CBoxHard::Initialize()
{
    m_tInfo = { m_tInfo.fX, m_tInfo.fY, 50.f, 50.f };
    
}

int CBoxHard::Update()
{
	if (m_bIsDead == true)
	{
		return OBJ_DEAD;
	}

	__super::UpdateRect();
	return OBJ_NOEVENT;
}

void CBoxHard::LateUpdate()
{
}

void CBoxHard::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
	if (g_bDevmode) Hitbox(hDC, m_tRect);
}

void CBoxHard::Release()
{
}

void CBoxHard::OnCollision(CObject* _op)
{
}

void CBoxHard::OnBlockEvent()
{
}
