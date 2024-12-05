#include "pch.h"
#include "CLine.h"
#include "CScrollManager.h"

CLine::CLine()
{
}

CLine::CLine(LINEPOINT& tLeft, LINEPOINT& tRight) : m_tInfo(tLeft, tRight)
{
}

CLine::CLine(LINE& tLine) : m_tInfo(tLine)
{
}

CLine::~CLine()
{
}

void CLine::Render(HDC _hDC)
{
	int		iScrollX = (int)CScrollManager::Get_Instance()->Get_ScrollX();

	MoveToEx(_hDC, (int)m_tInfo.tLPoint.fX + iScrollX, (int)m_tInfo.tLPoint.fY, nullptr);
	LineTo(_hDC, (int)m_tInfo.tRPoint.fX + iScrollX, (int)m_tInfo.tRPoint.fY);
}
