#include "pch.h"
#include "CMainGame.h"
#include "CAbstractFactory.h"
#include "CObjectManager.h"
#include "CPlayer.h"
#include "CLineManager.h"
#include "CKeyManager.h"
#include "CItemDH.h"
#include "CBoxItem.h"
#include "CBoxHard.h"
#include "CBitmapManager.h"
#include "CSceneManager.h"


bool g_bDevmode = false;

CMainGame::CMainGame() : m_ullTime(GetTickCount64()), m_iFPS(0), m_hDC(nullptr)
{
	ZeroMemory(&m_szFPS, sizeof(m_szFPS));
	ZeroMemory(&m_szPlayer, sizeof(m_szPlayer));
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);	


	// TODO :: 맵 임의 생성.
	/*CObjectManager::GetInstance()->Add_Object(OBJ_BOX, CAbstractFactory<CBoxHard>::Create(500, 350));
	CObjectManager::GetInstance()->Add_Object(OBJ_BOX, CAbstractFactory<CBoxItem>::Create(550, 350));*/

	//CBitmapManager::GetInstance()->InsertBitmap(RESORUCEPATH L"BackBuffer/BackBuffer.bmp", L"Back");
	//CBitmapManager::GetInstance()->InsertBitmap(RESORUCEPATH L"Map/1-1.bmp", L"Ground");
	CSceneManager::GetInstance()->Initialize();
}

void CMainGame::Update()
{
	CSceneManager::GetInstance()->Update();
	KeyInput();

}

void CMainGame::LateUpdate()
{
	CKeyManager::GetInstance()->Update();
	CSceneManager::GetInstance()->LateUpdate();
}

void CMainGame::Render()
{
#pragma region  FPS 출력
	++m_iFPS;

	if (m_ullTime + 1000 < GetTickCount64())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);

		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_ullTime = GetTickCount64();
	}
#pragma endregion
	CSceneManager::GetInstance()->Render(m_hDC);
	//HDC		hMemDC = CBitmapManager::GetInstance()->FindImage(L"Back");
	//HDC		hGroundDC = CBitmapManager::GetInstance()->FindImage(L"Ground");

	//BitBlt(hMemDC, 0, 0, WINCX, WINCY, hGroundDC, 0, 0, SRCCOPY);

	////Background
	//
	////LineManager
	//CLineManager::GetInstance()->Render(m_hDC);
	////ObjectManager
	//

	//BitBlt(m_hDC,
	//	0, 0, WINCX, WINCY,
	//	hMemDC,
	//	0,
	//	0,
	//	SRCCOPY);

	//if (g_bDevmode)
	//{
	//	TextOut(m_hDC, 0, 0, L"DevMode", lstrlenW(L"DevMode"));
	//	swprintf(m_szPlayer, sizeof(m_szPlayer), L"X: %.2f Y: %.2f", CObjectManager::GetInstance()->GetPlayer()->GetINFO().fX, CObjectManager::GetInstance()->GetPlayer()->GetINFO().fY);
	//	TextOut(m_hDC, 0, 40, m_szPlayer, lstrlenW(m_szPlayer));
	//}
}

void CMainGame::Release()
{
	CBitmapManager::DestroyInstance();
	CScrollManager::DestroyInstance();
	CKeyManager::DestroyInstance();
	CLineManager::DestroyInstance();
	CObjectManager::DestroyInstance();
	ReleaseDC(g_hWnd, m_hDC);
}

void CMainGame::KeyInput()
{
	if (CKeyManager::GetInstance()->KeyDown(VK_F2))
	{
		g_bDevmode = !g_bDevmode;
	}
}

