#include "pch.h"
#include "StageScene.h"
#include "Player.h"
#include "Monster.h"

StageScene::StageScene()
{
}

StageScene::~StageScene()
{
}

void StageScene::Initialize(Obj* _pPlayer)
{
	m_ObjList[OBJ_PLAYER].push_back(_pPlayer);
	static_cast<Player*>(m_ObjList[OBJ_PLAYER].front())->Set_Bullet(&m_ObjList[OBJ_BULLET]);
}

int StageScene::Update()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
			pObj->Update();
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
}

void StageScene::Render(HDC _hDC)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
			pObj->Render(_hDC);
	}
}

void StageScene::Release()
{
}

void StageScene::SpawnMonster()
{
	//몬스터 스폰
}
