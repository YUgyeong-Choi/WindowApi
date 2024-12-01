#include "pch.h"
#include "StageScene.h"
#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "BulletItem.h"
#include "HealItem.h"
#include "ShootSpeedItem.h"
#include "PSpeedItem.h"
#include "ShieldItem.h"
#include "CollisionMgr.h"

StageScene::StageScene() : m_ullTime(0), m_bFinish(false), m_bStart(true) , m_ullStartTime(0)
{
}

StageScene::~StageScene()
{
	Release();
}

void StageScene::Initialize(Obj* _pPlayer)
{
	m_ObjList[OBJ_PLAYER].push_back(_pPlayer);
	static_cast<Player*>(m_ObjList[OBJ_PLAYER].front())->Set_Bullet(&m_ObjList[OBJ_BULLET]);
	static_cast<Player*>(m_ObjList[OBJ_PLAYER].front())->Set_Shield(&m_ObjList[OBJ_SHIELD]);
	
	m_ullTime = GetTickCount64();

}

int StageScene::Update()
{
	if (m_bFinish) {
		return OBJ_CLEAR;
	}
	if (m_bStart)
	{
		m_ullStartTime =  GetTickCount64();
		m_ullStartTime += 30000;
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

void StageScene::Late_Update()
{

	CollisionMgr::Collision_Circle(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET]); //∏ÛΩ∫≈Õ & √—æÀ
	CollisionMgr::Collision_Rect(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_PLAYER]); //∏ÛΩ∫≈Õ & «√∑π¿ÃæÓ
	CollisionMgr::Collision_Circle(m_ObjList[OBJ_SHIELD], m_ObjList[OBJ_MONSTER]); //∏ÛΩ∫≈Õ & ΩØµÂ
	CollisionMgr::Collision_Circle(m_ObjList[OBJ_ITEM], m_ObjList[OBJ_PLAYER]); //æ∆¿Ã≈€ & «√∑π¿ÃæÓ
	CollisionMgr::Collision_Circle(m_ObjList[OBJ_MONSTERBULLET], m_ObjList[OBJ_PLAYER]); //∏ÛΩ∫≈Õ & «√∑π¿ÃæÓ
	CollisionMgr::Collision_Circle(m_ObjList[OBJ_MONSTERBULLET], m_ObjList[OBJ_SHIELD]); //∏ÛΩ∫≈Õ√—æÀ & ΩØµÂ

	if ((m_ullStartTime - GetTickCount64()) / 1000 <= 0) {
		m_bFinish = true;
	}

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
			pObj->Late_Update();
	}
}

void StageScene::Render(HDC _hDC)
{
	Rectangle(_hDC, int(GAME_WIN_LEFT), int(GAME_WIN_TOP), int(GAME_WIN_RIGHT), int(GAME_WIN_BOTTOM));

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
			pObj->Render(_hDC);
	}

	TCHAR szBullet[32];
	wsprintf(szBullet, L"Bullet: %d", (int)m_ObjList[OBJ_BULLET].size());
	TextOut(_hDC, 50, 50, szBullet, lstrlen(szBullet));

	TCHAR szMonster[32];
	wsprintf(szMonster, L"Monster: %d", (int)m_ObjList[OBJ_MONSTER].size());
	TextOut(_hDC, 150, 50, szMonster, lstrlen(szMonster));

	TCHAR szPlayerHp[32];
	wsprintf(szPlayerHp, L"PlayerHp: %d", m_ObjList[OBJ_PLAYER].front()->Get_Hp());
	TextOut(_hDC, 250, 50, szPlayerHp, lstrlen(szPlayerHp));


	TCHAR szTimer[32];
	wsprintf(szTimer, L"Time: %d", int((m_ullStartTime - GetTickCount64()) / 1000));
	TextOut(_hDC, 350, 50, szTimer, lstrlen(szTimer));
}

void StageScene::Release() 
{
	for (size_t i = 1; i < OBJ_END; ++i) {
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<Obj*>);
		m_ObjList->clear();
	}
}


void StageScene::SpawnMonster()
{
}

void StageScene::SpawnItem(float _x, float _y)
{
	int iRate = rand() % 100; 
	int iRandomItem = rand() % 100;
	if (0 <= iRate && iRate < 30) {  // 10% »Æ∑¸
		if (0 <= iRandomItem && iRandomItem < 15) {  // 15% »Æ∑¸ 
			m_ObjList[OBJ_ITEM].push_back(new BulletItem());
		}
		else if (15 <= iRandomItem && iRandomItem < 55) {  // 40% »Æ∑¸ 
			m_ObjList[OBJ_ITEM].push_back(new HealItem());
		}
		else if (55 <= iRandomItem && iRandomItem < 70) {  // 15% »Æ∑¸ 
			m_ObjList[OBJ_ITEM].push_back(new ShootSpeedItem());
		}
		else if (70 <= iRandomItem && iRandomItem < 85) {  // 15% »Æ∑¸ 
			m_ObjList[OBJ_ITEM].push_back(new PSpeedItem());
		}
		else if (85 <= iRandomItem && iRandomItem < 100) {// 15% »Æ∑¸ 
			m_ObjList[OBJ_ITEM].push_back(new ShieldItem());
		}

		m_ObjList[OBJ_ITEM].back()->Set_Pos(_x, _y);
		m_ObjList[OBJ_ITEM].back()->Initialize();
		m_ObjList[OBJ_ITEM].back()->Set_Target(m_ObjList[OBJ_PLAYER].front());
	}
}
