#pragma once
#include "Define.h"

class CMainGame
{
public:
	CMainGame();
	virtual ~CMainGame() { Release(); }

	void		Initialize();
	void		Update();
	void		LateUpdate();
	void		Render();
	void		Release();
	void		KeyInput();
private:
	HDC			m_hDC;

	ULONG64		m_ullTime;
	TCHAR		m_szPlayer[36];
	TCHAR		m_szFPS[16];
	int			m_iFPS;
};