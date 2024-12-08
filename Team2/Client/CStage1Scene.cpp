#include "pch.h"
#include "CStage1Scene.h"
#include "Define.h"
#include "CObjectManager.h"
#include "CPlayer.h"
#include "CAbstractFactory.h"

void CStage1Scene::Initialize()
{
	CObjectManager::GetInstance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
	Load();
}

int CStage1Scene::Update()
{
	CObjectManager::GetInstance()->Update();
	if (GetAsyncKeyState(VK_F1))
	{
		return OBJ_CLEAR;
	}
	return 0;
}

void CStage1Scene::LateUpdate()
{
	CObjectManager::GetInstance()->LateUpdate();
}

void CStage1Scene::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);
	CObjectManager::GetInstance()->Render(hDC);
}
