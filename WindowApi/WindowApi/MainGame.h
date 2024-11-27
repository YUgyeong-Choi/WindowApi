#pragma once

#include "Define.h"
#include "pch.h"
#include <Windows.h>

#include "Player.h"
#include "Monster.h"

class MainGame
{
public:
	MainGame();
	~MainGame();
public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Render();
	void Release();
private:
	void GameStart();
	void SpawnMonster();
private:
	HDC m_hDC;
	list<Obj*> m_ObjList[OBJ_END];

	ULONGLONG	m_dwTime;
	int			m_iFPS;
	TCHAR		m_szFPS[16];
};

