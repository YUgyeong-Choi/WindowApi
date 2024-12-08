#include "pch.h"
#include "Define.h"
#include "CSceneManager.h"
#include "CAbstractFactory.h"
#include "CObjectManager.h"

#include "CStartScene.h"
#include "CStageKL.h"
#include "CStageSH.h"
#include "CStageDH.h"
#include "CStageMH.h"
#include "CStageYK.h"

CSceneManager* CSceneManager::m_pInstance = nullptr;

void CSceneManager::Initialize()
{
	m_Scenes.push_back(new CStartScene);
	m_Scenes.push_back(new CStageKL);
	m_Scenes.push_back(new CStageSH);
	m_Scenes.push_back(new CStageDH);
	m_Scenes.push_back(new CStageMH);
	m_Scenes.push_back(new CStageYK);

	m_Scenes.at(m_SceneNum)->Initialize();
}

void CSceneManager::Update()
{
	int checkStage = m_Scenes.at(m_SceneNum)->Update();
	switch (checkStage)
	{
	case OBJ_NOEVENT:
		break;
	case OBJ_DEAD:
		m_SceneNum = 0;
		CObjectManager::GetInstance()->Release();
		m_Scenes.at(m_SceneNum)->Initialize();
		break;
	case OBJ_FINISH:
		m_SceneNum = 0;
		CObjectManager::GetInstance()->Release();
		m_Scenes.at(m_SceneNum)->Initialize();
		break;
	case OBJ_KL:
		m_SceneNum = 1;
		CObjectManager::GetInstance()->Release();
		m_Scenes.at(m_SceneNum)->Initialize();
		break;
	case OBJ_SH:
		m_SceneNum = 2;
		CObjectManager::GetInstance()->Release();
		m_Scenes.at(m_SceneNum)->Initialize();
		break;
	case OBJ_DH:
		m_SceneNum = 3;
		CObjectManager::GetInstance()->Release();
		m_Scenes.at(m_SceneNum)->Initialize();
		break;
	case OBJ_MH:
		m_SceneNum = 4;
		CObjectManager::GetInstance()->Release();
		m_Scenes.at(m_SceneNum)->Initialize();
		break;
	case OBJ_YK:
		m_SceneNum = 5;
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

CSceneManager::CSceneManager() : m_SceneNum(0)
{

}