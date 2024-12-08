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
		// 최초 일 때

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
	HANDLE		hFile = CreateFile(L"../Data/Line.dat", // 파일 경로와 이름을 명시
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

	for (auto& pLine : m_LineList[LINE_NONE])
	{
		WriteFile(hFile, pLine->GetInfo(), sizeof(LINE), &dwByte, nullptr);
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Save 완료"), L"성공", MB_OK);
}

void CLineManager::LoadLine()
{
	Release();

	HANDLE		hFile = CreateFile(L"../Data/Line.dat", // 파일 경로와 이름을 명시
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
	LINE	tLine{};

	while (true)
	{
		ReadFile(hFile, &tLine, sizeof(LINE), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_LineList[LINE_NONE].push_back(new CLine(tLine));
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load 완료"), L"성공", MB_OK);
}
