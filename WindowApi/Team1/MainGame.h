#pragma once
#include "Define.h"
#include "SceneObj.h"

class MainGame
{
public:
	MainGame();
	~MainGame();
public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(); 
private:
	HDC m_hDC;
	SceneObj* m_SceneArray[SCENE::NONE];
	SCENE m_iScene;
};

