#pragma once
#include "Define.h"
class CSceneManager
{
public:

	void ReadSaveFile();
	void LoadScene();

	static CSceneManager* GetInstance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CSceneManager;

		return m_pInstance;
	}

	static void	DestroyInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	CSceneManager();
	~CSceneManager() {};

	static CSceneManager* m_pInstance;
};

