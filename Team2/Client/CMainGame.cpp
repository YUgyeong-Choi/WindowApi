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

	//CLineManager::GetInstance()->Initialize();

	//CObjectManager::GetInstance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayerDH>::Create());	

	// TODO :: 맵 임의 생성.
	/*CObjectManager::GetInstance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockHard>::Create(500, 350));
	CObjectManager::GetInstance()->Add_Object(OBJ_BLOCK, CAbstractFactory<CBlockItem>::Create(550, 350));*/

	//Load();

	//CBitmapManager::GetInstance()->InsertBitmap(RESORUCEPATH L"BackBuffer/BackBuffer.bmp", L"Back");
	//CBitmapManager::GetInstance()->InsertBitmap(RESORUCEPATH L"Map/1-1.bmp", L"Ground");
	CSceneManager::GetInstance()->Initialize();
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

void CMainGame::Load()
{
	HANDLE		hFile = CreateFile(L"../Data/Box.dat", // 파일 경로와 이름을 명시
		GENERIC_READ,		// 파일 접근 모드(GENERIC_READ)
		NULL,				// 공유 방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈 할 때 허용할 것인가
		NULL,				// 보안 속성, NULL인 경우 기본 보안 상태
		OPEN_EXISTING,		// 생성 방식(CREATE_ALWAYS : 파일어 없으면 생성, 있으면 덮어 쓰기, OPEN_EXISTING : 파일 있을 경우에만 열기)
		FILE_ATTRIBUTE_NORMAL, // 파일 속성, 아무런 속성이 없는 일반 파일의 형식으로 생성
		NULL);				// 생성될 파일의 속성을 제공할 템플릿 파일(안쓰니 NULL)

	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte(0);
	CBlock	cBlock;

	int i = 0;
	while (true)
	{
		ReadFile(hFile, &cBlock, sizeof(CBlock), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CObject* obj = nullptr;

		if (cBlock.GetBlockType() == BLOCKTYPE::BLOCK_HARD)
		{
			obj = CAbstractFactory<CBlockHard>::Create(cBlock.GetINFO().fX, cBlock.GetINFO().fY);
		}
		else if (cBlock.GetBlockType() == BLOCKTYPE::BLOCK_ITEM)
		{
			obj = CAbstractFactory<CBlockItem>::Create(cBlock.GetINFO().fX, cBlock.GetINFO().fY);
		}

		if (obj == nullptr)
		{
			continue;
		}

		CObjectManager::GetInstance()->Add_Object(OBJ_BLOCK, obj);
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load 완료"), L"성공", MB_OK);
}
