#include "pch.h"
#include "CMainGame.h"
#include "CAbstractFactory.h"
#include "CObjectManager.h"
#include "CPlayerDH.h"
#include "CLineManager.h"
#include "CKeyManager.h"
#include "CItemDH.h"
#include "CBlockItem.h"
#include "CBlockHard.h"
#include "CBitmapManager.h"
#include "CBlockHard.h"
#include "CBlockItem.h"
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
	CSceneManager::GetInstance()->Initialize();

	CBitmapManager::GetInstance()->InsertBitmap(RESORUCEPATH L"BackBuffer/BackBuffer.bmp", L"Back");
	CBitmapManager::GetInstance()->InsertBitmap(RESORUCEPATH L"Map/Back.bmp", L"Ground");

	//Register bitmap image files for render Mario
	CBitmapManager::GetInstance()->InsertBitmap(RESORUCEPATH L"Player/SmallMario/SmallMarioLeft.bmp", L"SmallMarioLeft");
	CBitmapManager::GetInstance()->InsertBitmap(RESORUCEPATH L"Player/SmallMario/SmallMarioRight.bmp", L"SmallMarioRight");
	CBitmapManager::GetInstance()->InsertBitmap(RESORUCEPATH L"Player/BigMario/BigMarioLeft.bmp", L"BigMarioLeft");
	CBitmapManager::GetInstance()->InsertBitmap(RESORUCEPATH L"Player/BigMario/BigMarioRight.bmp", L"BigMarioRight");
	CBitmapManager::GetInstance()->InsertBitmap(RESORUCEPATH L"Player/FireMario/FireMarioLeft.bmp", L"FireMarioLeft");
	CBitmapManager::GetInstance()->InsertBitmap(RESORUCEPATH L"Player/FireMario/FireMarioRight.bmp", L"FireMarioRight");

	//Register bitmap image files for render Item
	CBitmapManager::GetInstance()->InsertBitmap(RESORUCEPATH L"Item/Item.bmp", L"Items");
}

void CMainGame::Update()
{
	KeyInput();
	//CObjectManager::GetInstance()->Update();
	CSceneManager::GetInstance()->Update();
}

void CMainGame::LateUpdate()
{
	//CObjectManager::GetInstance()->LateUpdate();
	//CKeyManager::GetInstance()->Update();

	CKeyManager::GetInstance()->Update();
	CSceneManager::GetInstance()->LateUpdate();
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

	CSceneManager::GetInstance()->Render(m_hDC);
	//HDC		hMemDC = CBitmapManager::GetInstance()->FindImage(L"Back");
	//HDC		hGroundDC = CBitmapManager::GetInstance()->FindImage(L"Ground");
	//
	//BitBlt(hMemDC, 0, 0, WINCX, WINCY, hGroundDC, 0, 0, SRCCOPY);
	//
	////Background
	//Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	////LineManager
	//CLineManager::GetInstance()->Render(m_hDC);
	////ObjectManager
	//CObjectManager::GetInstance()->Render(m_hDC);
	//
	//BitBlt(m_hDC,
	//	0, 0, WINCX, WINCY,
	//	hMemDC,
	//	0,
	//	0,
	//	SRCCOPY);

	if (g_bDevmode)
	{
		TextOut(m_hDC, 0, 0, L"DevMode", lstrlenW(L"DevMode"));
		swprintf(m_szPlayer, sizeof(m_szPlayer), L"X: %.2f Y: %.2f", CObjectManager::GetInstance()->GetPlayer()->GetINFO().fX, CObjectManager::GetInstance()->GetPlayer()->GetINFO().fY);
		TextOut(m_hDC, 0, 40, m_szPlayer, lstrlenW(m_szPlayer));
	}
}

void CMainGame::Release()
{
	CBitmapManager::DestroyInstance();
	CScrollManager::DestroyInstance();
	CKeyManager::DestroyInstance();
	CLineManager::DestroyInstance();
	CObjectManager::DestroyInstance();
	CSceneManager::DestroyInstance();
	ReleaseDC(g_hWnd, m_hDC);
}

void CMainGame::KeyInput()
{
	if (CKeyManager::GetInstance()->KeyDown(VK_F2))
	{
		g_bDevmode = !g_bDevmode;
	}
}