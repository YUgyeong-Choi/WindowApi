#pragma once
#include "Define.h"
#include "CObject.h"
class CObjectManager
{
private:
	CObjectManager();
	CObjectManager(const CObjectManager& rhs) = delete;
	CObjectManager operator =(CObject& rObj) = delete;
	~CObjectManager();
public:
	void		Add_Object(OBJID _objID, CObject* _pObj);
	int			Update();
	void		Late_Update();
	void		Render(HDC _hDC);
	void		Release();
public:
	static CObjectManager* Get_Instance()
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
	list<CObject*>		m_ObjList[OBJ_END];

	static CObjectManager* m_pInstance;
};

