#include "pch.h"
#include "Stage2.h"
#include "Monster.h"

Stage2::Stage2()
{
}

Stage2::~Stage2()
{
}

void Stage2::SpawnMonster()
{
	if (m_dwTime + 700 < GetTickCount64()) {
		m_dwTime = GetTickCount64();
		m_ObjList[OBJ_MONSTER].push_back(new Monster());
		m_ObjList[OBJ_MONSTER].back()->Initialize();
		m_ObjList[OBJ_MONSTER].back()->Set_Target(m_ObjList[OBJ_PLAYER].front());
	}
}
