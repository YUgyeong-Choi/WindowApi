#pragma once
#include "CObject.h"
class CRectangleManager
{
public:
	void	Initialize();
	int		 Update();
	void	Render(HDC hDC);
	void	Release();

	list<CObject*>* GetList()
	{
		return m_RectList;
	}

	static CRectangleManager* GetInstance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CRectangleManager;

		return m_pInstance;
	}

	static void	DestroyInstance()
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
private:
	CRectangleManager();
	~CRectangleManager() { Release(); }
	static CRectangleManager* m_pInstance;
	list<CObject*> m_RectList[RECT_END];
};

