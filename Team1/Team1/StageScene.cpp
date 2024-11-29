#include "pch.h"
#include "StageScene.h"
#include "Player.h"
#include "Monster.h"
#include "Satellite.h"
#include "CollisionMgr.h"

StageScene::StageScene() : m_dwTime(0), bFinish(false)
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
	
	m_dwTime = GetTickCount64();
}

int StageScene::Update()
{
	if (bFinish) {
		return OBJ_CLEAR;
	}

	SpawnMonster();

	for (size_t i = 0; i < OBJ_END; ++i) {
		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end();) {
			int result = (*iter)->Update();

			if (OBJ_DEAD == result) {
				if (static_cast<Player*>(*iter)) {
					return OBJ_DEAD;
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
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
			pObj->Late_Update();
	}

	CollisionMgr::Collision_Circle(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET]);

	if (m_ObjList[OBJ_MONSTER].size() == 0) {
		bFinish = true;
	}
}

void StageScene::Render(HDC _hDC)
{

	Rectangle(_hDC, (int)GAME_WIN_LEFT, (int)GAME_WIN_TOP, (int)GAME_WIN_RIGHT, (int)GAME_WIN_BOTTOM);
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
	if (m_dwTime + 1000 < GetTickCount64()) {
		m_dwTime = GetTickCount64();
		m_ObjList[OBJ_MONSTER].push_back(new Monster());
		m_ObjList[OBJ_MONSTER].back()->Initialize();
	}
}
