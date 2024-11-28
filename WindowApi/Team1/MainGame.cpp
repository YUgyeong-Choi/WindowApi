#include "pch.h"
#include "MainGame.h"
#include "StartScene.h"
#include "StageScene.h"
#include "EndScene.h"

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}

void MainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	m_SceneArray[START] = new StartScene;
	m_SceneArray[STAGE_ONE] = new StageScene;
	m_SceneArray[END] = new EndScene;

	for (auto& sceneObj : m_SceneArray) {
		sceneObj->Initialize();
	}
}

void MainGame::Update()
{
	m_SceneArray[m_iScene]->Update();
}

void MainGame::Late_Update()
{
}

void MainGame::Render()
{
}
