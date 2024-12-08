#include "pch.h"
#include "Define.h"
#include "CSceneManager.h"
#include "CStage1Scene.h"
#include "CStage2Scene.h"
#include "CStartScene.h"
#include "CEndScene.h"
#include "CAbstractFactory.h"
#include "CObjectManager.h"

CSceneManager* CSceneManager::m_pInstance = nullptr;

void CSceneManager::Initialize()
{
	m_Scenes.push_back(new CStartScene);
	m_Scenes.push_back(new CStage1Scene);
	m_Scenes.push_back(new CStage2Scene);
	m_Scenes.push_back(new CEndScene);

	m_Scenes.at(m_SceneNum)->Initialize();
}

void CSceneManager::Update()
{
	int checkStage = m_Scenes.at(m_SceneNum)->Update();
	switch (checkStage)
	{
	case OBJ_NOEVENT:
		break;
	case OBJ_CLEAR:
		m_SceneNum++;
		CObjectManager::GetInstance()->Release();
		m_Scenes.at(m_SceneNum)->Initialize();
		break;
	case OBJ_DEAD:
		break;
	case OBJ_FINISH:
		m_SceneNum = 0;
		CObjectManager::GetInstance()->Release();
		m_Scenes.at(m_SceneNum)->Initialize();
		break;
	default:
		break;
	}

	
}

void CSceneManager::LateUpdate()
{
	m_Scenes.at(m_SceneNum)->LateUpdate();
}

void CSceneManager::Render(HDC hDC)
{
	m_Scenes.at(m_SceneNum)->Render(hDC);
}

CSceneManager::CSceneManager(): m_SceneNum(0)
{

}
