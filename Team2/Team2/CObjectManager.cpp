#include "pch.h"
#include "CObjectManager.h"

CObjectManager* CObjectManager::m_pInstance = nullptr;

CObjectManager::CObjectManager()
{
}

CObjectManager::~CObjectManager()
{
	Release();
}

void CObjectManager::Add_Object(OBJID _objID, CObject* _pObj)
{
	if (OBJ_END <= _objID || nullptr == _pObj)
		return;

	m_ObjList[_objID].push_back(_pObj);
}

int CObjectManager::Update()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObject*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}

	return 0;
}

void CObjectManager::Late_Update()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
			pObj->Late_Update();
	}
}

void CObjectManager::Render(HDC hDC)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
			pObj->Render(hDC);
	}
}

void CObjectManager::Release()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObject*>);
		m_ObjList[i].clear();
	}
}
