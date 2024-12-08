#include "pch.h"
#include "Define.h"
#include "CSceneObject.h"
#include "CObject.h"
#include "CAbstractFactory.h"
#include "CObjectManager.h"
#include "CBlockHard.h"
#include "CBlockItem.h"

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

void CSceneObject::Load(const TCHAR* _name)
{
	TCHAR url[100];

	_stprintf_s(url, _T("../Data/%s.dat"), _name);

	HANDLE		hFile = CreateFile(url, // ���� ��ο� �̸��� ���
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
	CBlock	cBox;

	int i = 0;
	while (true)
	{
		ReadFile(hFile, &cBox, sizeof(CBlock), &dwByte, nullptr);

		if (0 == dwByte)
			break;
		CObject* obj = nullptr;
		if (cBox.GetBlockType() == BLOCK_HARD) {
			obj  = CAbstractFactory<CBlockHard>::Create(cBox.GetINFO().fX, cBox.GetINFO().fY);
			
		}
		else if (cBox.GetBlockType() == BLOCK_ITEM) {
			obj = CAbstractFactory<CBlockItem>::Create(cBox.GetINFO().fX, cBox.GetINFO().fY);
		}

		if (obj == nullptr) {
			continue;
		}

		CObjectManager::GetInstance()->Add_Object(OBJ_BLOCK, obj);
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load �Ϸ�"), L"����", MB_OK);
}
