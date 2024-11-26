#pragma once

#include "Define.h"
#include "Player.h"
#include "pch.h"
#include <Windows.h>

class MainGame
{
public:
	MainGame();
	~MainGame();
public:
	void Initialize();
	void Update();
	void Render();
	void Release();
private:
	void CheckOut();
private:
	HDC m_hDC;
	Obj* m_pPlayer;
	list<Obj*> m_BulletList;
};

