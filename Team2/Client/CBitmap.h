#pragma once
class CBitmap
{
public:
	CBitmap();
	~CBitmap() { Release(); }

	HDC		GetMemDC() { return m_hMemDC; }
	void	LoadBitmap(const TCHAR* pFilePath);
	void	Release();
private:
	HDC		m_hMemDC;
	HBITMAP m_hBitmap;
	HBITMAP m_hOldmap;
};

