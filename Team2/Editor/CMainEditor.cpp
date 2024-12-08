#include "pch.h"
#include "CMainEditor.h"
#include "../Client/CScrollManager.h"
#include "../Client/CLineManager.h"
#include "../Client/CKeyManager.h"

bool g_bDevmode = false;

CMainEditor::CMainEditor() : m_ullTime(GetTickCount64()), m_iFPS(0), m_hDC(nullptr)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

void CMainEditor::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	CLineManager::GetInstance()->Initialize();
}

void CMainEditor::Update()
{
	CLineManager::GetInstance()->Update();
}

void CMainEditor::Late_Update()
{
	CKeyManager::GetInstance()->Update();
	CLineManager::GetInstance()->LateUpdate();
}

void CMainEditor::Render()
{
#pragma region  FPS Ãâ·Â
	++m_iFPS;

	if (m_ullTime + 1000 < GetTickCount64())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);

		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_ullTime = GetTickCount64();
	}
#pragma endregion
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	CLineManager::GetInstance()->Render(m_hDC);

}

void CMainEditor::Release()
{
	CScrollManager::DestroyInstance();
	CKeyManager::DestroyInstance();
	CLineManager::DestroyInstance();
	ReleaseDC(g_hWnd, m_hDC);
}
