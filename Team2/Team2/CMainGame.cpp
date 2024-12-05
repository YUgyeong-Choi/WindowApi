#include "pch.h"
#include "CMainGame.h"
#include "CObjectManager.h"

CMainGame::CMainGame()
{
}

CMainGame::~CMainGame()
{
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);
}

void CMainGame::Update()
{
}

void CMainGame::Late_Update()
{
}

void CMainGame::Render()
{
}

void CMainGame::Release()
{
}
