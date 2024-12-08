#include "pch.h"
#include "CStageYK.h"
#include "Define.h"
#include "CObjectManager.h"
#include "CPlayerYK.h"
#include "CAbstractFactory.h"
#include "CMonsterYK1.h"
#include "CMonsterBossYK.h"

void CStageYK::Initialize()
{
	CObjectManager::GetInstance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayerYK>::Create());
	CObjectManager::GetInstance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonsterYK1>::Create());
	CObjectManager::GetInstance()->GetLastMonster()->SetTargetObject(CObjectManager::GetInstance()->GetPlayer());
	CObjectManager::GetInstance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonsterBossYK>::Create());
	CObjectManager::GetInstance()->GetLastMonster()->SetTargetObject(CObjectManager::GetInstance()->GetPlayer());
	Load();
}

int CStageYK::Update()
{
	if (OBJ_DEAD == CObjectManager::GetInstance()->Update()) {
		return OBJ_DEAD;
	}
	
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
