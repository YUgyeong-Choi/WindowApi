#include "pch.h"
#include "CStageDH.h"
#include "Define.h"
#include "CObjectManager.h"
#include "CPlayerDH.h"
#include "CAbstractFactory.h"

void CStageDH::Initialize()
{
	CObjectManager::GetInstance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayerDH>::Create());
	Load();
}

int CStageDH::Update()
{
	CObjectManager::GetInstance()->Update();
	if (GetAsyncKeyState(VK_F9))
	{
		return OBJ_FINISH;
	}
	return 0;
}

void CStageDH::LateUpdate()
{
	CObjectManager::GetInstance()->LateUpdate();
}

void CStageDH::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);
	CObjectManager::GetInstance()->Render(hDC);
}
