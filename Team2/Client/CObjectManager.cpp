#include "pch.h"
#include "../Client/CObjectManager.h"
#include "../Client/CCollisionManager.h"
#include "../Client/CLineManager.h"

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
}

void CObjectManager::FixedUpdate()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjectList[i])
			pObj->FixedUpdate();
	}
	CCollisionManager::CollisionLine(m_ObjectList[OBJ_PLAYER].front(), CLineManager::GetInstance()->GetList()[LINE_NONE]);
	CCollisionManager::CollisionRectEx2(m_ObjectList[OBJ_PLAYER], m_ObjectList[OBJ_NONE]);
	CCollisionManager::CollisionRectEx2(m_ObjectList[OBJ_PLAYER], m_ObjectList[OBJ_BOX]);
	CCollisionManager::CollisionRectEx2(m_ObjectList[OBJ_PLAYER], m_ObjectList[OBJ_ITEM]);
	CCollisionManager::CollisionRectEx2(m_ObjectList[OBJ_ITEM], m_ObjectList[OBJ_BOX]);
	CCollisionManager::CollisionRectEx2(m_ObjectList[OBJ_ITEM], m_ObjectList[OBJ_NONE]);
	/*CCollisionManager::CollisionTestRect(m_ObjectList[OBJ_PLAYER], m_ObjectList[OBJ_ITEM]);
	CCollisionManager::CollisionTestRect(m_ObjectList[OBJ_PLAYER], m_ObjectList[OBJ_MONSTER]);
	CCollisionManager::CollisionTestRect(m_ObjectList[OBJ_ITEM], m_ObjectList[OBJ_BOX]);
	CCollisionManager::CollisionTestRect(m_ObjectList[OBJ_MONSTER], m_ObjectList[OBJ_BOX]);
	CCollisionManager::CollisionTestRect(m_ObjectList[OBJ_MONSTER], m_ObjectList[OBJ_NONE]);
	CCollisionManager::CollisionTestRect(m_ObjectList[OBJ_ITEM], m_ObjectList[OBJ_NONE]);*/
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
				Safe_Delete<CObject*>(*iter);
				iter = m_ObjectList[i].erase(iter);
			}
			else
				++iter;
		}
	}
	//
	return 0;
}

void CObjectManager::LateUpdate()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjectList[i])
			pObj->LateUpdate();
	}

	///CCollisionManager::CollisionLine(m_ObjectList[OBJ_PLAYER], CLineManager::GetInstance()->GetList()[LINE_NONE]);
	
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
