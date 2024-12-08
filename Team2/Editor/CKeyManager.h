#pragma once
#include "Define.h"

class CKeyManager
{
public:
	bool		KeyPressing(int _iKey);
	bool		KeyDown(int _iKey);			// µü ÇÑ ¹ø ´­·¶À» ¶§
	bool		KeyUp(int _iKey);			// ´­·¶´Ù°¡ ¶ÃÀ» ¶§
	void		Update();

	static CKeyManager* GetInstance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CKeyManager;

		return m_pInstance;
	}

	static void	DestroyInstance()
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}

private:
	CKeyManager();
	~CKeyManager() {};

	static CKeyManager* m_pInstance;
	bool	m_bKeyState[VK_MAX];
};

