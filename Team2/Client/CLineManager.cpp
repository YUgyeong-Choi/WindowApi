#include "pch.h"
#include "CLineManager.h"

CLineManager* CLineManager::m_pInstance = nullptr;

void CLineManager::Initialize()
{
	m_LineList[LINE_NONE].push_back(new CLine(Vector<float>{-100, 500}, Vector<float>{1000, 500}));
}

void CLineManager::Render(HDC hDC)
{
	for (size_t i = 0; i < LINE_END; ++i)
	{
		for (auto& line : m_LineList[i])
			line->Render(hDC);
	}
}

void CLineManager::Release()
{
}

void CLineManager::LoadLine()
{
}

CLineManager::CLineManager()
{

}
