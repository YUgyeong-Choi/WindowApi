#include "pch.h"
#include "CMainGame.h"
#include "CObjectManager.h"
#include "CAbstractFactory.h"
#include "CLineManager.h"

CMainGame::CMainGame(): m_hDC(nullptr)
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);
	CLineManager::Get_Instance()->Initialize();
	CObjectManager::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
}

void CMainGame::Update()
{
	CObjectManager::Get_Instance()->Update();
}

void CMainGame::Late_Update()
{
	CObjectManager::Get_Instance()->Late_Update();
}

void CMainGame::Render()
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	CLineManager::Get_Instance()->Render(m_hDC);
	CObjectManager::Get_Instance()->Render(m_hDC);
}

void CMainGame::Release()
{
	CObjectManager::DestroyInstance();
	ReleaseDC(g_hWnd, m_hDC);
}
