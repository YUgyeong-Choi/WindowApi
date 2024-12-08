#pragma once
#include "Define.h"
#include "CMouse.h"
class CMouseManager
{
public:
	

	bool		ButtonPressing(int _iButton);
	bool		ButtonDown(int _iKey);			// µü ÇÑ ¹ø ´­·¶À» ¶§
	bool		ButtonUp(int _iKey);			// ´­·¶´Ù°¡ ¶ÃÀ» ¶§
	void		Update();

	static CMouseManager* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CMouseManager;

		return m_pInstance;
	}

	static void	Destroy_Instance()
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}

private:
	CMouseManager();
	~CMouseManager() {};

	static	CMouseManager* m_pInstance;
	bool	m_bButtonState[VK_MAX];
};