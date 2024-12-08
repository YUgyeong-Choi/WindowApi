#pragma once
#include "../Client/CObject.h"
class CObjectManager
{
public:
	CObject* GetPlayer() 
	{ 
		if (!m_ObjectList[OBJ_PLAYER].empty()) return m_ObjectList[OBJ_PLAYER].front();
		else return nullptr;
	}
	CObject* GetLastMonster() { return m_ObjectList[OBJ_MONSTER].back(); }

	list<CObject*> GetList() { return m_ObjectList[OBJ_NONE]; }

	CObject* GetTarget(OBJID eID, CObject* pDst);

	void		Add_Object(OBJID eID, CObject* pObj);
	void		FixedUpdate();
	int			Update();
	void		LateUpdate();
	void		Render(HDC hDC);
	void		Release();

	static CObjectManager* GetInstance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CObjectManager;

		return m_pInstance;
	}

	static void		DestroyInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	CObjectManager();
	~CObjectManager() { Release(); }
	CObjectManager(const CObjectManager& rhs) = delete;
	CObject operator =(CObject& rObj) = delete;

	static CObjectManager* m_pInstance;
	list<CObject*> m_ObjectList[OBJID::OBJ_END];
};

