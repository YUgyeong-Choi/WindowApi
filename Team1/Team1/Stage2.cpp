#include "pch.h"
#include "Stage2.h"
#include "MonsterB1.h"

Stage2::Stage2()
{
}

Stage2::~Stage2()
{
}

void Stage2::SpawnMonster()
{
	if (m_ullTime + 700 < GetTickCount64()) {
		m_ullTime = GetTickCount64();
		m_ObjList[OBJ_MONSTER].push_back(new MonsterB1());
		static_cast<Monster*>(m_ObjList[OBJ_MONSTER].back())->Set_Bullet(&m_ObjList[OBJ_MONSTERBULLET]);
		m_ObjList[OBJ_MONSTER].back()->Initialize();
		m_ObjList[OBJ_MONSTER].back()->Set_Target(m_ObjList[OBJ_PLAYER].front());
	}
}
