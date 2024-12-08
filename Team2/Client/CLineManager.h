#pragma once
#include "CLine.h"
class CLineManager
{
public:
	void	Initialize();
	int		Update();
	void	LateUpdate();
	void	Render(HDC hDC);
	void	Release();

	void		AddLine(LINETYPE eID, CLine* pObj);

	void	SaveLine();
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
	CLineManager()
	{
		ZeroMemory(m_tLinePoint, sizeof(m_tLinePoint));
	}
	~CLineManager() { Release(); }
	static CLineManager* m_pInstance;
	list<CLine*>		m_LineList[LINE_END];
	Vector<float>		m_tLinePoint[DIR_END];
};

