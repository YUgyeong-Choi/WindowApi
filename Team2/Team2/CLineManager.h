#pragma once
#include "Define.h"
#include "CLine.h"
class CLineManager
{
private:
	CLineManager();
	~CLineManager();
public:
	bool	Collision_Line(float _fX, float* pY);

public:
	void	Initialize();
	void	Render(HDC hDC);
	void	Release();

public:
	static CLineManager* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CLineManager;

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


private:
	static CLineManager* m_pInstance;
	list<CLine*>			m_Linelist;
	LINEPOINT				m_tLinePoint[DIR_END];

};