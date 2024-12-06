#include "pch.h"
#include "CObjectManager.h"
#include "CCollisionManager.h"
#include "CRectangleManager.h"

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
	m_ObjectList[eID].back()->SetOID(eID);
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
	return 0;
}

void CObjectManager::LateUpdate()
{
	CCollisionManager::CollisionRect(m_ObjectList[OBJ_PLAYER], CRectangleManager::GetInstance()->GetList()[RECT_NONE]);
	CCollisionManager::CollisionRect(m_ObjectList[OBJ_PLAYER], CRectangleManager::GetInstance()->GetList()[RECT_ITEM]);
	CCollisionManager::CollisionRect(m_ObjectList[OBJ_ITEM], CRectangleManager::GetInstance()->GetList()[RECT_NONE]);

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
