#pragma once
#include "Define.h"
#include "CSceneObject.h"

class CSceneManager
{
public:

	//void ReadSaveFile();
	//void LoadScene();

	void Initialize();
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();

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
	~CSceneManager() { Release(); }

	static CSceneManager* m_pInstance;

	vector<CSceneObject*> m_Scenes;
	int m_SceneNum;

};



