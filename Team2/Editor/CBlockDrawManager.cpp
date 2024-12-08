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
		MessageBox(g_hWnd, _T("������ ������ ������ ����"), L"â", MB_OK);
	}
	else if (CKeyManager::GetInstance()->KeyUp(VK_F2))
	{
		m_CurrentType = BLOCKTYPE::BLOCK_HARD;
		MessageBox(g_hWnd, _T("���� �� �μ����� ������ ����"), L"â", MB_OK);
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

	// �� ����.
	if (CKeyManager::GetInstance()->KeyUp(VK_LBUTTON))
	{
		// ���� ����.
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

		// ���� ����.
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
	HANDLE		hFile = CreateFile(L"../Data/Box.dat", // ���� ��ο� �̸��� ���
		GENERIC_WRITE,		// ���� ���� ���(GENERIC_READ)
		NULL,				// ���� ���, ������ �����ִ� ���¿��� �ٸ� ���μ����� ���� �� �� ����� ���ΰ�
		NULL,				// ���� �Ӽ�, NULL�� ��� �⺻ ���� ����
		CREATE_ALWAYS,		// ���� ���(CREATE_ALWAYS : ���Ͼ� ������ ����, ������ ���� ����, OPEN_EXISTING : ���� ���� ��쿡�� ����)
		FILE_ATTRIBUTE_NORMAL, // ���� �Ӽ�, �ƹ��� �Ӽ��� ���� �Ϲ� ������ �������� ����
		NULL);				// ������ ������ �Ӽ��� ������ ���ø� ����(�Ⱦ��� NULL)

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

	MessageBox(g_hWnd, _T("Save �Ϸ�"), L"����", MB_OK);
}
