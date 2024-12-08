#pragma once
#include "CLine.h"
class CLineManager
{
public:
	void	Initialize();

	void	Render(HDC hDC);
	void	Release();

	void	LoadLine();

	list<CLine*>* GetList()
	{
		return m_LineList;
	}

	static CLineManager* GetInstance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CLineManager;

		return m_pInstance;
	}

	static void	DestroyInstance()
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
private:
	CLineManager();
	~CLineManager() { Release(); }
	static CLineManager* m_pInstance;
	list<CLine*> m_LineList[LINE_END];
};

