#include "pch.h"
#include "CLine.h"
#include "CScrollManager.h"

CLine::CLine() 
{
	ZeroMemory(&m_LPoint, sizeof(POINT));
	ZeroMemory(&m_RPoint, sizeof(POINT));
}

void CLine::Initialize()
{
}

int CLine::Update()
{
	return OBJ_NOEVENT;
}

void CLine::LateUpdate()
{
}

void CLine::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollManager::GetInstance()->GetScrollX();

	MoveToEx(hDC, m_LPoint.GetX() + iScrollX, m_LPoint.GetY(), nullptr);
	LineTo(hDC, m_RPoint.GetX() + iScrollX, m_RPoint.GetY());
}

void CLine::Release()
{
}
