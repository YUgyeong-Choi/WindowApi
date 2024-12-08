#pragma once
#include "pch.h"
#include "CBlockHard.h"
#include "CBlockItem.h"

class CBlockDrawManager
{
public:
	void	Initialize();
	int		Update();
	void	Late_Update();
	void	Render(HDC hDC);
	void	Release();

	void	Save_Line();

public:
	static CBlockDrawManager* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CBlockDrawManager;

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
	static CBlockDrawManager* m_pInstance;
	list<CBlock*> m_ListOfBox;

	// ���� ���� �� ����.
	int m_WidthBoxCount = 0;
	int m_HeightBoxCount = 0;

	// ù Ŭ�� ���콺 ��ǥ.
	POINT m_FirstClick;

	// ���� �������� �ڽ� Ÿ��.
	BLOCKTYPE m_CurrentType;
};

