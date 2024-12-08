#include "pch.h"
#include "Define.h"
#include "CSceneObject.h"
#include "CObject.h"
#include "CAbstractFactory.h"
#include "CObjectManager.h"
#include "CBoxHard.h"

void CSceneObject::Initialize()
{
}

int CSceneObject::Update()
{
	return OBJ_NOEVENT;
}

void CSceneObject::LateUpdate()
{
}

void CSceneObject::Render(HDC hDC)
{
}

void CSceneObject::Load()
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
	CBoxHard	cBox;

	int i = 0;
	while (true)
	{
		ReadFile(hFile, &cBox, sizeof(CBoxHard), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CObject* obj = CAbstractFactory<CBoxHard>::Create(cBox.GetINFO().fX, cBox.GetINFO().fY);
		CObjectManager::GetInstance()->Add_Object(OBJ_BOX, obj);
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load 완료"), L"성공", MB_OK);
}
