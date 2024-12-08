#pragma once
#include "Define.h"

class CMainGame
{
public:
	CMainGame(): m_ullTime(GetTickCount64()), m_iFPS(0), m_hDC(nullptr),
				 m_iPlayerX(0), m_iPlayerY(0)
	{
		ZeroMemory(&m_szFPS, sizeof(m_szFPS));
		ZeroMemory(&m_szPlayer, sizeof(m_szPlayer));
	}
	virtual ~CMainGame() { Release(); }

	void		Initialize();
	void		FixedUpdate();
	void		Update();
	void		LateUpdate();
	void		Render();
	void		Release();
	void		KeyInput();
private:
	HDC			m_hDC;

	ULONG64		m_ullTime;
	TCHAR		m_szFPS[16];
	TCHAR		m_szPlayer[36];
	int			m_iPlayerX;
	int			m_iPlayerY;
	int			m_iFPS;
};