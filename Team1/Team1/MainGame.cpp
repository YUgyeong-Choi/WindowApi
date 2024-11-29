#include "pch.h"
#include "MainGame.h"
#include "StartScene.h"
#include "StageScene.h"
#include "EndScene.h"
#include "Player.h"

MainGame::MainGame() :m_hDC(nullptr), m_pPlayer(nullptr), m_iScene(NONE)
{
	ZeroMemory(m_SceneArray, sizeof(m_SceneArray));
}

MainGame::~MainGame()
{
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
	m_SceneArray[STAGE_ONE] = new StageScene;
	m_SceneArray[END] = new EndScene;

	for (auto& sceneObj : m_SceneArray) {
		sceneObj->Initialize(m_pPlayer);
	}
}

int MainGame::Update()
{
	int result = m_SceneArray[m_iScene]->Update();
	if (result == OBJ_CLEAR) {
		return OBJ_CLEAR;
	}

	if (result == OBJ_FINISH) {
		return OBJ_FINISH;
	}

	return OBJ_NOEVENT;
}

void MainGame::Late_Update()
{
	m_SceneArray[m_iScene]->Late_Update();
}

void MainGame::Render()
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	m_SceneArray[m_iScene]->Render(m_hDC);
}

void MainGame::Release()
{
	for (auto& sceneObj : m_SceneArray) {
		Safe_Delete<SceneObj*>(sceneObj);
	}
	Safe_Delete<Obj*>(m_pPlayer);
}
