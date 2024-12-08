#include "pch.h"
#include "CMainGame.h"
#include "CBlockDrawManager.h"
#include "CKeyManager.h"

bool g_bDevmode = false;

CMainGame::CMainGame() : m_ullTime(GetTickCount64()), m_iFPS(0), m_hDC(nullptr)
{
	ZeroMemory(&m_szFPS, sizeof(m_szFPS));
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	CBlockDrawManager::Get_Instance()->Initialize();
}

void CMainGame::Update()
{
	KeyInput();	

	CBlockDrawManager::Get_Instance()->Update();
}

void CMainGame::LateUpdate()
{	
	CKeyManager::GetInstance()->Update();
	CBlockDrawManager::Get_Instance()->Late_Update();
}

void CMainGame::Render()
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


	//Background
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	CBlockDrawManager::Get_Instance()->Render(m_hDC);

	if(g_bDevmode) TextOut(m_hDC, 0, 0, L"DevMode", lstrlenW(L"DevMode"));
}

void CMainGame::Release()
{
	CBlockDrawManager::Get_Instance()->Render(m_hDC);
	ReleaseDC(g_hWnd, m_hDC);
}

void CMainGame::KeyInput()
{
}
