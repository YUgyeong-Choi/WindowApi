#include "pch.h"
#include "Define.h"
#include "CSceneObject.h"
#include "CObject.h"
#include "CAbstractFactory.h"
#include "CObjectManager.h"
#include "CBlockHard.h"

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
	HANDLE		hFile = CreateFile(L"../Data/Box.dat", // ���� ��ο� �̸��� ���
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
	CBlockHard	cBox;

	int i = 0;
	while (true)
	{
		ReadFile(hFile, &cBox, sizeof(CBlockHard), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CObject* obj = CAbstractFactory<CBlockHard>::Create(cBox.GetINFO().fX, cBox.GetINFO().fY);
		CObjectManager::GetInstance()->Add_Object(OBJ_BLOCK, obj);
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load �Ϸ�"), L"����", MB_OK);
}
