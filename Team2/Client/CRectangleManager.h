#pragma once
#include "CObject.h"
class CRectangleManager
{
public:
	void	Initialize();
	int		 Update();
	void	Render(HDC hDC);
	void	Release();

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
};

