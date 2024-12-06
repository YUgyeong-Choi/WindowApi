#include "pch.h"
#include "CMouseManager.h"

CMouseManager* CMouseManager::m_pInstance = nullptr;

CMouseManager::CMouseManager()
{
	ZeroMemory(&m_bButtonState, sizeof(m_bButtonState));
}

bool CMouseManager::ButtonPressing(int _iButton)
{
	return false;
}

bool CMouseManager::ButtonDown(int _iKey)
{
	return false;
}

bool CMouseManager::ButtonUp(int _iKey)
{
	return false;
}

void CMouseManager::Update()
{
}
