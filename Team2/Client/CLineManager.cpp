#include "pch.h"
#include "CLineManager.h"

CLineManager* CLineManager::m_pInstance = nullptr;

void CLineManager::Initialize()
{
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
