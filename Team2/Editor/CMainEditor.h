#pragma once
class CMainEditor
{
public:
	CMainEditor();
	~CMainEditor() { Release(); }
	void		Initialize();
	void		Update();
	void		Late_Update();
	void		Render();
	void		Release();
private:
	HDC			m_hDC;

	ULONG64		m_ullTime;
	int			m_iFPS;
	TCHAR		m_szFPS[16];
};