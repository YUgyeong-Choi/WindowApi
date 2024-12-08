#include "pch.h"
#include "CLine.h"
#include "CScrollManager.h"

CLine::CLine() 
{
	ZeroMemory(&m_LPoint, sizeof(POINT));
	ZeroMemory(&m_RPoint, sizeof(POINT));
}

CLine::CLine(LINEPOINT& tLeft, LINEPOINT& tRight) : m_tInfo(tLeft, tRight)
{
}

CLine::CLine(LINE& tInfo) : m_tInfo(tInfo)
{
}

void CLine::Initialize()
{
	m_fSpeed = 10.f;
}

int CLine::Update()
{
	m_LPoint.x += 10.f;
	m_RPoint.x += 10.f;
	return OBJ_NOEVENT;
}

void CLine::LateUpdate()
{
	
	m_tInfo.tLPoint.fX = -CScrollManager::GetInstance()->GetScrollX() + 10;
	m_tInfo.tRPoint.fX = -CScrollManager::GetInstance()->GetScrollX() + 10;
	m_LPoint.x = m_tInfo.tLPoint.fX;
	m_RPoint.x = m_tInfo.tRPoint.fX;
}

void CLine::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollManager::GetInstance()->GetScrollX();

	Line(hDC, m_LPoint, m_RPoint, { CScrollManager::GetInstance()->GetScrollX() , 0 });
	if (g_bDevmode) HitLine(hDC, m_LPoint, m_RPoint, { CScrollManager::GetInstance()->GetScrollX() , 0});

	/*MoveToEx(hDC, (int)m_tInfo.tLPoint.fX + iScrollX, (int)m_tInfo.tLPoint.fY, nullptr);
	LineTo(hDC, (int)m_tInfo.tRPoint.fX + iScrollX, (int)m_tInfo.tRPoint.fY);*/
}

void CLine::Release()
{

}

float CLine::GetCurrentY(float _fX)
{
	float x1 = m_LPoint.GetX();
	float y1 = m_LPoint.GetY();
	float x2 = m_RPoint.GetX();
	float y2 = m_RPoint.GetY();
	float cY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;
	return cY;
}
