#include "pch.h"
#include "CLine.h"

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
	MoveToEx(_hDC, (int)m_tInfo.tLPoint.fX , (int)m_tInfo.tLPoint.fY, nullptr);
	LineTo(_hDC, (int)m_tInfo.tRPoint.fX , (int)m_tInfo.tRPoint.fY);
}
