#include "pch.h"
#include "CStageKL.h"
#include "Define.h"
#include "CObjectManager.h"
#include "CPlayerDH.h"
#include "CAbstractFactory.h"

void CStageKL::Initialize()
{
	CObjectManager::GetInstance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayerDH>::Create());
	Load();
}

int CStageKL::Update()
{
	CObjectManager::GetInstance()->Update();
	if (GetAsyncKeyState(VK_F9))
	{
		return OBJ_FINISH;
	}
	return 0;
}

void CStageKL::LateUpdate()
{
	CObjectManager::GetInstance()->LateUpdate();
}

void CStageKL::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);
	CObjectManager::GetInstance()->Render(hDC);
}
