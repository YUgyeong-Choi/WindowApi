#include "pch.h"
#include "CBoxDrawManager.h"
#include "Define.h"
#include "CKeyManager.h"
#include "CScrollManager.h"

CBoxDrawManager* CBoxDrawManager::m_pInstance = nullptr;

void CBoxDrawManager::Initialize()
{
}

int CBoxDrawManager::Update()
{
	POINT	ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	ptMouse.x -= (int)CScrollManager::GetInstance()->GetScrollX();

	if (CKeyManager::GetInstance()->KeyDown(VK_LBUTTON))
	{
		m_BoxCount = 1;

		m_FirstClick.x = (float)ptMouse.x;
		m_FirstClick.y = (float)ptMouse.y;
	}

	if (CKeyManager::GetInstance()->KeyPressing(VK_LBUTTON))
	{
		if (m_FirstClick.x + 50.f <= ptMouse.x)
		{
			m_BoxCount++;
			m_FirstClick.x = ptMouse.x;
		}
	}

	if (CKeyManager::GetInstance()->KeyUp(VK_LBUTTON))
	{
		for (int i = 0; i < m_BoxCount; i++)
		{
			m_ListOfBox.push_back(new CBoxHard());
			m_ListOfBox.back()->SetPos(m_FirstClick.x - (50 * i), m_FirstClick.y);
			m_ListOfBox.back()->SetSize(50.f, 50.f);
			m_ListOfBox.back()->UpdateRect();
		}

		m_BoxCount = 0;
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

void CBoxDrawManager::Late_Update()
{
}

void CBoxDrawManager::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollManager::GetInstance()->GetScrollX();
	for (auto& box : m_ListOfBox)
	{		
		Rectangle(hDC, box->GetRECT(), { (float)iScrollX , 0.f});
	}
}

void CBoxDrawManager::Release()
{
}

void CBoxDrawManager::Save()
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
		WriteFile(hFile, pBox, sizeof(CBoxHard), &dwByte, nullptr);
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Save �Ϸ�"), L"����", MB_OK);
}
