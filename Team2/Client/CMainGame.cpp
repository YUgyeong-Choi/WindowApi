#include "pch.h"
#include "CMainGame.h"


//Objects
#include "CBox.h"
#include "CBoss.h"
#include "CPlayer.h"
#include "CMHPlayer.h"

//Managers
#include "CAbstractFactory.h"
#include "CObjectManager.h"
#include "CLineManager.h"
#include "CKeyManager.h"
#include "CBitmapManager.h"
#include "CScrollManager.h"



bool g_bDevmode = false;

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	CLineManager::GetInstance()->Initialize();

	//플레이어 생성
	CObjectManager::GetInstance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CMHPlayer>::Create());
	//CObjectManager::GetInstance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CBoss>::Create());

	/*CObjectManager::GetInstance()->Add_Object(OBJ_NONE, CAbstractFactory<CBox>::Create(0, 100, Vector<float>{50.f, 50.f}));
	CObjectManager::GetInstance()->Add_Object(OBJ_NONE, CAbstractFactory<CBox>::Create(49, 100, Vector<float>{50.f, 50.f}));
	CObjectManager::GetInstance()->Add_Object(OBJ_NONE, CAbstractFactory<CBox>::Create(98,100, Vector<float>{50.f, 50.f}));
	CObjectManager::GetInstance()->Add_Object(OBJ_NONE, CAbstractFactory<CBox>::Create(147,100, Vector<float>{50.f, 50.f}));
	CObjectManager::GetInstance()->Add_Object(OBJ_NONE, CAbstractFactory<CBox>::Create(196,100, Vector<float>{50.f, 50.f}));*/

	
	//CObjectManager::GetInstance()->Add_Object(OBJ_NONE, CAbstractFactory<CBox>::Create(500, WINCY/2, Vector<float>{50.f, 50.f}));

	for (int i = 0; i < 5; ++i)
	{
		CObjectManager::GetInstance()->Add_Object(OBJ_NONE, CAbstractFactory<CBox>::Create(i * 49, 350, Vector<float>{50.f, 50.f}));
	}


	for (int i = -30; i < 30; ++i)
	{
		CObjectManager::GetInstance()->Add_Object(OBJ_NONE, CAbstractFactory<CBox>::Create(i * 49, 500, Vector<float>{50.f, 50.f}));
	}


	for (int i = 1; i < 10; ++i)
	{
		CObjectManager::GetInstance()->Add_Object(OBJ_NONE, CAbstractFactory<CBox>::Create(490, 500 - i * 49, Vector<float>{50.f, 50.f}));
	}
	
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

void CMainGame::FixedUpdate()
{
	CObjectManager::GetInstance()->FixedUpdate();
}

void CMainGame::Update()
{
	KeyInput();
	CObjectManager::GetInstance()->Update();
}

void CMainGame::LateUpdate()
{
	CLineManager::GetInstance()->LateUpdate();
	CObjectManager::GetInstance()->LateUpdate();
	CKeyManager::GetInstance()->Update();
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

	HDC		hMemDC = CBitmapManager::GetInstance()->FindImage(L"Back");
	HDC		hGroundDC = CBitmapManager::GetInstance()->FindImage(L"Ground");

	BitBlt(hMemDC, 0, 0, WINCX, WINCY, hGroundDC, 0, 0, SRCCOPY);

	//Background
	//Rectangle(hGroundDC, 0, 0, WINCX, WINCY);
	//LineManager
	CLineManager::GetInstance()->Render(hMemDC);
	//ObjectManager
	CObjectManager::GetInstance()->Render(hMemDC);

	BitBlt(m_hDC,
		0, 0, WINCX, WINCY,
		hMemDC,
		0,
		0,
		SRCCOPY);

	if (g_bDevmode)
	{
		TextOut(m_hDC, 0, 0, L"DevMode", lstrlenW(L"DevMode"));
		if (CObjectManager::GetInstance()->GetPlayer())
		{
			swprintf(m_szPlayer, sizeof(m_szPlayer), L"X: %.2f Y: %.2f", CObjectManager::GetInstance()->GetPlayer()->GetINFO().fX, CObjectManager::GetInstance()->GetPlayer()->GetINFO().fY);
		}
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
	ReleaseDC(g_hWnd, m_hDC);
}

void CMainGame::KeyInput()
{
	if (CKeyManager::GetInstance()->KeyDown(VK_F2))
	{
		g_bDevmode = !g_bDevmode;
	}
}
