#include "pch.h"
#include "CRectangleManager.h"
#include "CNormalBlock.h"
#include "CSecretBlock.h"
#include "CBreakBlock.h"
#include "CWallBlock.h"
#include "CItemBlock.h"
#include "CObjectManager.h"
#include "CAbstractFactory.h"

CRectangleManager* CRectangleManager::m_pInstance = nullptr;

void CRectangleManager::Initialize()
{
	CObjectManager::GetInstance()->Add_Object(OBJ_RECT, CAbstractFactory<CNormalBlock>::Create(500.f,500.f));
	
	CObjectManager::GetInstance()->Add_Object(OBJ_RECT, CAbstractFactory<CWallBlock>::Create(-50.f,450.f));
	CObjectManager::GetInstance()->Add_Object(OBJ_RECT, CAbstractFactory<CWallBlock>::Create(350.f,450.f));
	CObjectManager::GetInstance()->Add_Object(OBJ_RECT, CAbstractFactory<CWallBlock>::Create(350.f,400.f));
	CObjectManager::GetInstance()->Add_Object(OBJ_RECT, CAbstractFactory<CWallBlock>::Create(350.f,350.f));
	CObjectManager::GetInstance()->Add_Object(OBJ_RECT, CAbstractFactory<CWallBlock>::Create(350.f,300.f));


	CObjectManager::GetInstance()->Add_Object(OBJ_RECT, CAbstractFactory<CBreakBlock>::Create(100.f, 300.f));
	CObjectManager::GetInstance()->Add_Object(OBJ_RECT, CAbstractFactory<CItemBlock>::Create(150.f, 300.f));
	CObjectManager::GetInstance()->Add_Object(OBJ_RECT, CAbstractFactory<CSecretBlock>::Create(200.f, 300.f));
}

int CRectangleManager::Update()
{
	return 0;
}

void CRectangleManager::Render(HDC hDC)
{

}

void CRectangleManager::Release()
{
}

CRectangleManager::CRectangleManager()
{
}
