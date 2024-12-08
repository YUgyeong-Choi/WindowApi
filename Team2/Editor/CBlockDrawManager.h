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

	// 저장.
	void Save();

private:
	static CBlockDrawManager* m_pInstance;
	list<CBlock*> m_ListOfBox;

	// 가로 생성 할 갯수.
	int m_WidthBoxCount = 0;
	int m_HeightBoxCount = 0;

	// 첫 클릭 마우스 좌표.
	POINT m_FirstClick;

	// 현재 선택중인 박스 타입.
	BLOCKTYPE m_CurrentType;
};

