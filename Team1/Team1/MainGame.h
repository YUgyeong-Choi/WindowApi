#pragma once
#include "Define.h"
#include "SceneObj.h"
#include "Obj.h"

class MainGame
{
public:
	MainGame();
	~MainGame();
public:
	void Initialize();
	int Update();
	void Late_Update();
	void Render(); 
	void Release();
public:
	void Load_Scene() { m_iScene++; m_SceneArray[m_iScene]->Initialize(m_pPlayer);}
	void PlayerDead_Render();
private:
	HDC m_hDC;
	SceneObj* m_SceneArray[SCENE::NONE];
	Obj* m_pPlayer;
	int m_iScene;
};

