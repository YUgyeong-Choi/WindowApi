#include "pch.h"
#include "CLineManager.h"
#include "CAbstractFactory.h"
#include "CKeyManager.h"
#include "CScrollManager.h"

CLineManager* CLineManager::m_pInstance = nullptr;

void CLineManager::Initialize()
{
	m_LineList[LINE_NONE].push_back(new CLine(Vector<float>{10, 0}, Vector<float>{10, 800}));

	/*m_LineList[LINE_NONE].push_back(new CLine(Vector<float>{0, 400}, Vector<float>{200, 400}));
	m_LineList[LINE_NONE].push_back(new CLine(Vector<float>{0, 100}, Vector<float>{200, 100}));

	m_LineList[LINE_NONE].push_back(new CLine(Vector<float>{-100, 300}, Vector<float>{900, 300}));
	m_LineList[LINE_NONE].push_back(new CLine(Vector<float>{-100, 200}, Vector<float>{800, 200}));
	m_LineList[LINE_NONE].push_back(new CLine(Vector<float>{-100, 100}, Vector<float>{700, 100}));*/


	/*m_LineList[LINE_NONE].push_back(new CLine(Vector<float>{100, 500}, Vector<float>{300, 500}));
	m_LineList[LINE_NONE].push_back(new CLine(Vector<float>{300, 500}, Vector<float>{700, 300}));
	m_LineList[LINE_NONE].push_back(new CLine(Vector<float>{200, 300}, Vector<float>{300, 300}));*/
}

int CLineManager::Update()
{
	POINT	ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	ptMouse.x -= (int)CScrollManager::GetInstance()->GetScrollX();

	if (CKeyManager::GetInstance()->KeyDown(VK_LBUTTON))
	{
		// ���� �� ��

		if ((!m_tLinePoint[LEFT].GetX()) && (!m_tLinePoint[LEFT].GetX()))
		{
			m_tLinePoint[LEFT].SetX((float)ptMouse.x);
			m_tLinePoint[LEFT].SetY((float)ptMouse.y);
		}

		else
		{
			m_tLinePoint[RIGHT].SetX((float)ptMouse.x);
			m_tLinePoint[RIGHT].SetY((float)ptMouse.y);

			m_LineList[LINE_NONE].push_back(new CLine(m_tLinePoint[LEFT], m_tLinePoint[RIGHT]));

			m_tLinePoint[LEFT].SetX(m_tLinePoint[RIGHT].GetX());
			m_tLinePoint[LEFT].SetY(m_tLinePoint[RIGHT].GetY());
		}
	}

	if (CKeyManager::GetInstance()->KeyDown('S'))
	{
		SaveLine();
		return 0;
	}

	if (CKeyManager::GetInstance()->KeyDown('L'))
	{
		LoadLine();
		return 0;
	}

	if (CKeyManager::GetInstance()->KeyPressing(VK_LEFT))
		CScrollManager::GetInstance()->SetScrollX(5.f);

	if (CKeyManager::GetInstance()->KeyPressing(VK_RIGHT))
		CScrollManager::GetInstance()->SetScrollX(-5.f);

	return 0;
}

void CLineManager::LateUpdate()
{
	for (size_t i = 0; i < LINE_END; ++i)
	{
		for (auto& pLine : m_LineList[i])
			pLine->LateUpdate();
	}
}

void CLineManager::Render(HDC hDC)
{
	for (size_t i = 0; i < LINE_END; ++i)
	{
		for (auto& line : m_LineList[i])
			line->Render(hDC);
	}
}

void CLineManager::Release()
{
}

void CLineManager::AddLine(LINETYPE eID, CLine* pObj)
{
	m_LineList[eID].push_back(CAbstractFactory<CLine>::Create());
}

void CLineManager::SaveLine()
{
	HANDLE		hFile = CreateFile(L"../Data/Line.dat", // ���� ��ο� �̸��� ���
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

	for (auto& pLine : m_LineList[LINE_NONE])
	{
		WriteFile(hFile, pLine->GetInfo(), sizeof(LINE), &dwByte, nullptr);
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Save �Ϸ�"), L"����", MB_OK);
}

void CLineManager::LoadLine()
{
	Release();

	HANDLE		hFile = CreateFile(L"../Data/Line.dat", // ���� ��ο� �̸��� ���
		GENERIC_READ,		// ���� ���� ���(GENERIC_READ)
		NULL,				// ���� ���, ������ �����ִ� ���¿��� �ٸ� ���μ����� ���� �� �� ����� ���ΰ�
		NULL,				// ���� �Ӽ�, NULL�� ��� �⺻ ���� ����
		OPEN_EXISTING,		// ���� ���(CREATE_ALWAYS : ���Ͼ� ������ ����, ������ ���� ����, OPEN_EXISTING : ���� ���� ��쿡�� ����)
		FILE_ATTRIBUTE_NORMAL, // ���� �Ӽ�, �ƹ��� �Ӽ��� ���� �Ϲ� ������ �������� ����
		NULL);				// ������ ������ �Ӽ��� ������ ���ø� ����(�Ⱦ��� NULL)

	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte(0);
	LINE	tLine{};

	while (true)
	{
		ReadFile(hFile, &tLine, sizeof(LINE), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_LineList[LINE_NONE].push_back(new CLine(tLine));
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load �Ϸ�"), L"����", MB_OK);
}
