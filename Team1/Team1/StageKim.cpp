#include "pch.h"
#include "StageKim.h"
#include "KBossMonster.h"
#include "Player.h"
#include "CollisionMgr.h"



StageKim::StageKim()
{
}

StageKim::~StageKim()
{
}

void StageKim::Initialize()
{
}

void StageKim::SpawnMonster()
{
	m_ObjList[OBJ_MONSTER].push_back(new KBossMonster());
	m_ObjList[OBJ_MONSTER].back()->Initialize();
	m_ObjList[OBJ_MONSTER].back()->Set_Target(m_ObjList[OBJ_PLAYER].front());
	static_cast<KBossMonster*>(m_ObjList[OBJ_MONSTER].back())->Set_Bullet(&m_ObjList[OBJ_BULLET_MONSTER]);
}

int StageKim::Update()
{
	if (GetAsyncKeyState(VK_SPACE)) {
		if (m_bFinish)
		{
			m_IsNext = !m_IsNext;
		}
	}

	if (m_IsNext) {
		return OBJ_CLEAR;
	}


	if (m_bStart)
	{
		m_ulStartTime = GetTickCount64();
		m_ulStartTime += 10000;
		SpawnMonster();

		// 2개
		/*auto iter = m_ObjList[OBJ_MONSTER].begin();
		(*iter)->Set_Pos((*iter)->Get_Info().fX - 100, (*iter)->Get_Info().fY);
		SpawnMonster();
		++iter;
		(*iter)->Set_Pos((*iter)->Get_Info().fX + 100, (*iter)->Get_Info().fY);*/


		m_bStart = false;
	}

	

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

void StageKim::Late_Update()
{
	// 아이템 충돌 제외
	CollisionMgr::Collision_Rect(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_PLAYER]); //몬스터 & 플레이어
	CollisionMgr::Collision_Rect(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET_PLAYER]); //몬스터 & 총알
	CollisionMgr::Collision_Circle(m_ObjList[OBJ_SHIELD], m_ObjList[OBJ_MONSTER]); //몬스터 & 쉴드

	CollisionMgr::Collision_Circle(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_BULLET_MONSTER]); // 플레이어 & 총알
	CollisionMgr::Collision_Circle(m_ObjList[OBJ_SHIELD], m_ObjList[OBJ_BULLET_MONSTER]); // 실드 & 총알


	if ((m_ulStartTime - GetTickCount64()) / 1000 <= 0) {
		m_bFinish = true;
	}

	if (m_ObjList[OBJ_MONSTER].size() == 0) {
		m_bFinish = true;
	}

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
			pObj->Late_Update();
	}

	
}