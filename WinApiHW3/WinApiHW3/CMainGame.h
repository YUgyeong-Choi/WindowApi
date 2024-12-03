#pragma once
#include "pch.h"
#include "CObj.h"

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
	void Release();
private:
	HDC m_hDC;
	Obj* m_pPlayer;
	vector<Obj*> m_pVecGround;
	int m_iWhatLine;
};

