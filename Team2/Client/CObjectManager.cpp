#include "pch.h"
#include "CObjectManager.h"
#include "CCollisionManager.h"
#include "CPlayerYK.h"

CObjectManager* CObjectManager::m_pInstance = nullptr;

CObject* CObjectManager::GetTarget(OBJID eID, CObject* pDst)
{
	return nullptr;
}

void CObjectManager::Add_Object(OBJID eID, CObject* pObj)
{
	if (OBJ_END <= eID || nullptr == pObj)
		return;

	m_ObjectList[eID].push_back(pObj);
	m_ObjectList[eID].back()->SetOBJID(eID);
}

int CObjectManager::Update()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjectList[i].begin();
			iter != m_ObjectList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				if (dynamic_cast<CPlayerYK*>(*iter)) {
					if ((*iter)->GetIsDead()) {
						return OBJ_DEAD;
					}
				}
				Safe_Delete<CObject*>(*iter);
				iter = m_ObjectList[i].erase(iter);
			}
			else
				++iter;
		} 
	}
	return 0;
}

void CObjectManager::LateUpdate()
{
	CCollisionManager::CollisionRectEx2(m_ObjectList[OBJ_PLAYER], m_ObjectList[OBJ_BLOCK]);
	CCollisionManager::CollisionRectEx2(m_ObjectList[OBJ_ITEM], m_ObjectList[OBJ_BLOCK]);
	CCollisionManager::CollisionRectEx2(m_ObjectList[OBJ_MONSTER], m_ObjectList[OBJ_BLOCK]);
	CCollisionManager::CollisionRectEx2(m_ObjectList[OBJ_PLAYER], m_ObjectList[OBJ_MONSTER]);
	CCollisionManager::CollisionRect(m_ObjectList[OBJ_PLAYER], m_ObjectList[OBJ_ITEM]);
	//CCollisionManager::CollisionRect(m_ObjectList[OBJ_PLAYER_BULLET], m_ObjectList[OBJ_MONSTER]);
	//CCollisionManager::CollisionRect(m_ObjectList[OBJ_PLAYER_BULLET], m_ObjectList[OBJ_BLOCK]);
	//CCollisionManager::CollisionCircle(m_ObjectList[OBJ_MONSTER_BULLET], m_ObjectList[OBJ_PLAYER]);

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjectList[i])
			pObj->LateUpdate();
	}
}

void CObjectManager::Render(HDC hDC)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjectList[i])
			pObj->Render(hDC);
	}
}

void CObjectManager::Release()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjectList[i].begin(), m_ObjectList[i].end(), Safe_Delete<CObject*>);
		m_ObjectList[i].clear();
	}
}

CObjectManager::CObjectManager()
{
}
