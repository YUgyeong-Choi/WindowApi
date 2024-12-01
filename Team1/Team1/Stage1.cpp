#include "pch.h"
#include "Stage1.h"
#include "Monster.h"
#include "MonsterShoot.h"
#include "Player.h"

Stage1::Stage1()
{
}

Stage1::~Stage1()
{
}

void Stage1::SpawnMonster()
{
	if (m_ulTime + 700 < GetTickCount64()) {
		m_ulTime = GetTickCount64();
		m_ObjList[OBJ_MONSTER].push_back(new MonsterShoot());
		m_ObjList[OBJ_MONSTER].back()->Initialize();
		m_ObjList[OBJ_MONSTER].back()->Set_Target(m_ObjList[OBJ_PLAYER].front());
		static_cast<MonsterShoot*>(m_ObjList[OBJ_MONSTER].back())->Set_Bullet(&m_ObjList[OBJ_BULLET_MONSTER]);

	}
	
}

int Stage1::Update()
{
	if (m_bFinish) {
		return OBJ_CLEAR;
	}
	if (m_bStart)
	{
		m_ulStartTime = GetTickCount64();
		m_ulStartTime += 50000;
		m_bStart = false;
	}

	SpawnMonster();

	for (size_t i = 0; i < OBJ_END; ++i) {
		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end();) {

			int result = (*iter)->Update();

			if (OBJ_DEAD == result) {
				if (dynamic_cast<Player*>(*iter)) {
					return OBJ_DEAD;
				}
				else if (dynamic_cast<Monster*>(*iter)) {
					SpawnItem((*iter)->Get_Info().fX, (*iter)->Get_Info().fY);
					Safe_Delete<Obj*>(*iter);
					iter = m_ObjList[i].erase(iter);
				}
				else {
					Safe_Delete<Obj*>(*iter);
					iter = m_ObjList[i].erase(iter);
				}
			}
			else {
				++iter;
			}
		}
	}
	return OBJ_NOEVENT;
}
