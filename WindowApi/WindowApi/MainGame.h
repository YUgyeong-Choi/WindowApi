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
	void Render();
	void Release();
private:
	void CheckOut();
	void MonsterDie();
	void SpawnMonster();
private:
	HDC m_hDC;
	Obj* m_pPlayer;
	list<Obj*> m_pMonsterList;
	list<Obj*> m_BulletList;

	ULONGLONG	m_dwTime;
	int			m_iFPS;
	TCHAR		m_szFPS[16];
};

