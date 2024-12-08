#include "pch.h"
#include "CBlockDrawManager.h"
#include "Define.h"
#include "CKeyManager.h"
#include "CScrollManager.h"

CBlockDrawManager* CBlockDrawManager::m_pInstance = nullptr;

void CBlockDrawManager::Initialize()
{
	m_CurrentType = BLOCKTYPE::BLOCK_ITEM;
}

int CBlockDrawManager::Update()
{
	POINT	ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	ptMouse.x -= (int)CScrollManager::GetInstance()->GetScrollX();

	if (CKeyManager::GetInstance()->KeyUp(VK_F1))
	{
		m_CurrentType = BLOCKTYPE::BLOCK_ITEM;
		MessageBox(g_hWnd, _T("아이템 나오는 벽으로 변경"), L"창", MB_OK);
	}
	else if (CKeyManager::GetInstance()->KeyUp(VK_F2))
	{
		m_CurrentType = BLOCKTYPE::BLOCK_HARD;
		MessageBox(g_hWnd, _T("절대 안 부서지는 벽으로 변경"), L"창", MB_OK);
	}

	if (CKeyManager::GetInstance()->KeyDown(VK_LBUTTON))
	{
		m_WidthBoxCount = 1;
		m_HeightBoxCount = 1;

		m_FirstClick.x = (float)ptMouse.x;
		m_FirstClick.y = (float)ptMouse.y;
	}

	if (CKeyManager::GetInstance()->KeyPressing(VK_LBUTTON))
	{
		if (m_FirstClick.x + 50.f <= ptMouse.x)
		{
			m_WidthBoxCount++;
			m_FirstClick.x = ptMouse.x;
		}

		if (m_FirstClick.y + 50.f <= ptMouse.y)
		{
			m_HeightBoxCount++;
			m_FirstClick.y = ptMouse.y;
		}
	}

	// 블럭 생성.
	if (CKeyManager::GetInstance()->KeyUp(VK_LBUTTON))
	{
		// 가로 생성.
		for (int i = 0; i < m_WidthBoxCount; i++)
		{
			if (m_CurrentType == BLOCKTYPE::BLOCK_HARD)
			{
				CBlock* boxHard = new CBlockHard();
				boxHard->SetBlockType(BLOCK_HARD);
				m_ListOfBox.push_back(boxHard);
			}
			else if (m_CurrentType == BLOCKTYPE::BLOCK_ITEM)
			{
				CBlock* boxItem = new CBlockItem();
				boxItem->SetBlockType(BLOCK_ITEM);
				m_ListOfBox.push_back(boxItem);
			}

			m_ListOfBox.back()->SetPos(m_FirstClick.x - (50.f * i), m_FirstClick.y);
			m_ListOfBox.back()->SetSize(50.f, 50.f);
			m_ListOfBox.back()->UpdateRect();
		}

		// 세로 생성.
		for (int i = 0; i < m_HeightBoxCount; i++)
		{
			if (m_CurrentType == BLOCKTYPE::BLOCK_HARD)
			{
				CBlock* boxHard = new CBlockHard();
				boxHard->SetBlockType(BLOCK_HARD);
				m_ListOfBox.push_back(boxHard);
			}
			else if (m_CurrentType == BLOCKTYPE::BLOCK_ITEM)
			{
				CBlock* boxItem = new CBlockItem();
				boxItem->SetBlockType(BLOCK_ITEM);
				m_ListOfBox.push_back(boxItem);
			}

			m_ListOfBox.back()->SetPos(m_FirstClick.x, m_FirstClick.y - (50.f * i));
			m_ListOfBox.back()->SetSize(50.f, 50.f);
			m_ListOfBox.back()->UpdateRect();
		}

		m_WidthBoxCount = 0;
		m_HeightBoxCount = 0;
	}

	if (CKeyManager::GetInstance()->KeyUp('S'))
	{
		Save();
		return 0;
	}

	if (CKeyManager::GetInstance()->KeyPressing(VK_LEFT))
		CScrollManager::GetInstance()->SetScrollX(5.f);

	if (CKeyManager::GetInstance()->KeyPressing(VK_RIGHT))
		CScrollManager::GetInstance()->SetScrollX(-5.f);

	return 0;
}

void CBlockDrawManager::Late_Update()
{
}

void CBlockDrawManager::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollManager::GetInstance()->GetScrollX();
	for (auto& box : m_ListOfBox)
	{
		Rectangle(hDC, box->GetRECT(), { (float)iScrollX , 0.f });
	}
}

void CBlockDrawManager::Release()
{
}

void CBlockDrawManager::Save()
{
	HANDLE		hFile = CreateFile(L"../Data/Box.dat", // 파일 경로와 이름을 명시
		GENERIC_WRITE,		// 파일 접근 모드(GENERIC_READ)
		NULL,				// 공유 방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈 할 때 허용할 것인가
		NULL,				// 보안 속성, NULL인 경우 기본 보안 상태
		CREATE_ALWAYS,		// 생성 방식(CREATE_ALWAYS : 파일어 없으면 생성, 있으면 덮어 쓰기, OPEN_EXISTING : 파일 있을 경우에만 열기)
		FILE_ATTRIBUTE_NORMAL, // 파일 속성, 아무런 속성이 없는 일반 파일의 형식으로 생성
		NULL);				// 생성될 파일의 속성을 제공할 템플릿 파일(안쓰니 NULL)

	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(g_hWnd, _T("Save File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte(0);

	for (auto& pBox : m_ListOfBox)
	{
		WriteFile(hFile, pBox, sizeof(CBlockHard), &dwByte, nullptr);
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Save 완료"), L"성공", MB_OK);
}
