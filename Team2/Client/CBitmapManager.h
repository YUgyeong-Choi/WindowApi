#pragma once
#include "CBitmap.h"
class CBitmapManager
{
public:

	void		InsertBitmap(const TCHAR* pFilePath, const TCHAR* pImgKey);
	HDC			FindImage(const TCHAR* pImgKey);
	void		Release();

	static CBitmapManager* GetInstance()
	{
		if (!m_pInstance) m_pInstance = new CBitmapManager;
		return m_pInstance;
	}

	static void DestroyInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	CBitmapManager();
	~CBitmapManager() { Release(); }
	static CBitmapManager* m_pInstance;
	map<const TCHAR*, CBitmap*>	m_mapBit;
};

