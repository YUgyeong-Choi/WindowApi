#include "pch.h"
#include "Stage1.h"
#include "MonsterB0.h"

Stage1::Stage1()
{
}

Stage1::~Stage1()
{
}

void Stage1::SpawnMonster()
{
	if (m_ullTime + 700 < GetTickCount64()) {
		m_ullTime = GetTickCount64();
		m_ObjList[OBJ_MONSTER].push_back(new MonsterB0());
		m_ObjList[OBJ_MONSTER].back()->Initialize();
		static_cast<Monster*>(m_ObjList[OBJ_MONSTER].back())->Set_Bullet(&m_ObjList[OBJ_MONSTERBULLET]);
		m_ObjList[OBJ_MONSTER].back()->Set_Target(m_ObjList[OBJ_PLAYER].front());
	}
}
