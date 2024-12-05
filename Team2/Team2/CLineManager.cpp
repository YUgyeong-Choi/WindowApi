#include "pch.h"
#include "CLineManager.h"
#include "CLine.h"

CLineManager* CLineManager::m_pInstance = nullptr;

CLineManager::CLineManager()
{
	ZeroMemory(m_tLinePoint, sizeof(m_tLinePoint));
}

CLineManager::~CLineManager()
{
	Release();
}


void CLineManager::Initialize()
{
	LINEPOINT tLeftLinePoint = { 100, 300 };
	LINEPOINT tRightLinePoint = { 600, 300 };
	LINE	tLine = { tLeftLinePoint, tRightLinePoint };
	LINEPOINT tLeftLinePoint2 = { 600, 300 };
	LINEPOINT tRightLinePoint2 = { 800, 500 };
	LINE	tLine2 = { tLeftLinePoint2, tRightLinePoint2 };
	m_Linelist.push_back(new CLine(tLine));
	m_Linelist.push_back(new CLine(tLine2));
}

void CLineManager::Render(HDC hDC)
{
	for (auto& pLine : m_Linelist)
		pLine->Render(hDC);
}

void CLineManager::Release()
{
	for_each(m_Linelist.begin(), m_Linelist.end(), Safe_Delete<CLine*>);
	m_Linelist.clear();
}

bool CLineManager::Collision_Line(float _fX, float* pY)
{
	if (m_Linelist.empty())
		return false;


	CLine* pTargetLine = nullptr;

	for (auto& pLine : m_Linelist)
	{
		if (_fX >= pLine->Get_Info().tLPoint.fX && _fX < pLine->Get_Info().tRPoint.fX)
		{
			pTargetLine = pLine;
		}
	}

	if (!pTargetLine)
		return false;

	float	x1 = pTargetLine->Get_Info().tLPoint.fX;
	float	y1 = pTargetLine->Get_Info().tLPoint.fY;
	float	x2 = pTargetLine->Get_Info().tRPoint.fX;
	float	y2 = pTargetLine->Get_Info().tRPoint.fY;

	*pY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;

	return true;
}
