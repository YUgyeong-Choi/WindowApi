#include "pch.h"
#include "CScrollManager.h"

CScrollManager* CScrollManager::m_pInstance = nullptr;

CScrollManager::CScrollManager() : m_fScrollX(0.f), m_fScrollY(0.f)
{
}