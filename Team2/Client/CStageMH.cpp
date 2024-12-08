#include "pch.h"
#include "CStageMH.h"
#include "Define.h"
#include "CObjectManager.h"
#include "CPlayerMH.h"
#include "CAbstractFactory.h"

void CStageMH::Initialize()
{
	CObjectManager::GetInstance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayerMH>::Create());
	Load();
}

int CStageMH::Update()
{
	CObjectManager::GetInstance()->Update();
	if (GetAsyncKeyState(VK_F9))
	{
		return OBJ_FINISH;
	}
	return 0;
}

void CStageMH::LateUpdate()
{
	CObjectManager::GetInstance()->LateUpdate();
}

void CStageMH::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);
	CObjectManager::GetInstance()->Render(hDC);
}
