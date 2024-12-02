#include "pch.h"
#include "MainGame.h"
#include "StartScene.h"
#include "StageScene.h"
#include "Stage2.h"
#include "StageYu.h"
#include "EndScene.h"
#include "Player.h"
#include "Stage1.h"

#include "StageHero.h"
#include "StageKim.h"
#include "StageCY.h"

MainGame::MainGame() :m_hDC(nullptr), m_pPlayer(nullptr), m_iScene(NONE)
{
	ZeroMemory(m_SceneArray, sizeof(m_SceneArray));
}

MainGame::~MainGame()
{
	Release();
}

void MainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);
	m_iScene = START;

	if (!m_pPlayer) {
		m_pPlayer = new Player;
		m_pPlayer->Initialize();
	}

	m_SceneArray[START] = new StartScene;
	m_SceneArray[STAGE_ONE] = new Stage1;
	m_SceneArray[STAGE_TWO] = new Stage2;
	m_SceneArray[STAGE_HERO] = new StageHero;
	m_SceneArray[STAGE_KIM] = new StageKim;
	m_SceneArray[STAGE_YU] = new StageYu;
	m_SceneArray[STAGE_CY] = new StageCY;
	m_SceneArray[END] = new EndScene;

	m_SceneArray[START]->Initialize(m_pPlayer);
}

int MainGame::Update()
{
	int result = m_SceneArray[m_iScene]->Update();
	if (result == OBJ_CLEAR) {
		return OBJ_CLEAR;
	}

	if (result == OBJ_FINISH) {
		PlayerWin_Render();
		return OBJ_FINISH;
	}

	if (result == OBJ_DEAD)
	{
		PlayerDead_Render();
		return OBJ_DEAD;
	}

	return OBJ_NOEVENT;
}

void MainGame::Late_Update()
{
	m_SceneArray[m_iScene]->Late_Update();
}

void MainGame::Render()
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_hDC, myBrush);
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	SelectObject(m_hDC, oldBrush);
	DeleteObject(myBrush);
	m_SceneArray[m_iScene]->Render(m_hDC);
}

void MainGame::Release()
{
	for (auto& sceneObj : m_SceneArray) {
		Safe_Delete<SceneObj*>(sceneObj);
	}
	Safe_Delete<Obj*>(m_pPlayer);
}

void MainGame::PlayerDead_Render()
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	HFONT newFont = CreateFont(50, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
	HFONT oldFont = (HFONT)SelectObject(m_hDC, newFont);
	TCHAR szTitleText[32];
	wsprintf(szTitleText, L"☹☹☹ Dead ☹☹☹");
	TextOut(m_hDC, WINCX / 2 - 200, WINCY / 2 - 150, szTitleText, lstrlen(szTitleText));
	SelectObject(m_hDC, oldFont);
	DeleteObject(newFont);
	Sleep(3000);
}


void MainGame::PlayerWin_Render()
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	HFONT newFont = CreateFont(50, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
	HFONT oldFont = (HFONT)SelectObject(m_hDC, newFont);
	TCHAR szTitleText[32];
	wsprintf(szTitleText, L"☹☹☹ Thank you for Playing ☹☹☹");
	TextOut(m_hDC, WINCX / 2 - 150, WINCY / 2 - 150, szTitleText, lstrlen(szTitleText));
	SelectObject(m_hDC, oldFont);
	DeleteObject(newFont);
	Sleep(3000);
}