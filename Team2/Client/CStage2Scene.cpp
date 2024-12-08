#include "pch.h"
#include "CStage2Scene.h"
#include "Define.h"
#include "CObjectManager.h"
#include "CPlayer.h"
#include "CAbstractFactory.h"

void CStage2Scene::Initialize()
{
	CObjectManager::GetInstance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
	Load();
}

int CStage2Scene::Update()
{
	CObjectManager::GetInstance()->Update();
	if (GetAsyncKeyState(VK_F1))
	{
		return OBJ_CLEAR;
	}
	return 0;
}

void CStage2Scene::LateUpdate()
{
	CObjectManager::GetInstance()->LateUpdate();
}

void CStage2Scene::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);
	CObjectManager::GetInstance()->Render(hDC);
}
