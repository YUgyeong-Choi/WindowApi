#pragma once
#include "pch.h"
#include "CBoxHard.h"
#include "CBoxItem.h"

class CBoxDrawManager
{
public:
	void	Initialize();
	int		Update();
	void	Late_Update();
	void	Render(HDC hDC);
	void	Release();

	void	Save_Line();

public:
	static CBoxDrawManager* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CBoxDrawManager;

		return m_pInstance;
	}

	static void	Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

	// ����.
	void Save();

private:
	static CBoxDrawManager* m_pInstance;
	list<CBoxHard*> m_ListOfBox;

	// ���� �� ����.
	int m_BoxCount = 0;

	// ù Ŭ�� ���콺 ��ǥ.
	POINT m_FirstClick;
};

