#include "pch.h"
#include "CStageYK.h"
#include "Define.h"
#include "CObjectManager.h"
#include "CPlayerDH.h"
#include "CAbstractFactory.h"

void CStageYK::Initialize()
{
	CObjectManager::GetInstance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayerDH>::Create());
	Load();
}

int CStageYK::Update()
{
	CObjectManager::GetInstance()->Update();
	if (GetAsyncKeyState(VK_F9))
	{
		return OBJ_FINISH;
	}
	return 0;
}

void CStageYK::LateUpdate()
{
	CObjectManager::GetInstance()->LateUpdate();
}

void CStageYK::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);
	CObjectManager::GetInstance()->Render(hDC);
}
