#include "pch.h"
#include "CStageSH.h"
#include "Define.h"
#include "CObjectManager.h"
#include "CPlayerDH.h"
#include "CAbstractFactory.h"

void CStageSH::Initialize()
{
	CObjectManager::GetInstance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayerDH>::Create());
	Load();
}

int CStageSH::Update()
{
	CObjectManager::GetInstance()->Update();
	if (GetAsyncKeyState(VK_F9))
	{
		return OBJ_FINISH;
	}
	return 0;
}

void CStageSH::LateUpdate()
{
	CObjectManager::GetInstance()->LateUpdate();
}

void CStageSH::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);
	CObjectManager::GetInstance()->Render(hDC);
}
