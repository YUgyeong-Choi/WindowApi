#include "pch.h"
#include "CBitmapManager.h"
#include "Define.h"

CBitmapManager* CBitmapManager::m_pInstance = nullptr;

void CBitmapManager::InsertBitmap(const TCHAR* pFilePath, const TCHAR* pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), tagFinder(pImgKey));

	if (iter == m_mapBit.end())
	{
		CBitmap* pMyBmp = new CBitmap;
		pMyBmp->LoadBitmap(pFilePath);

		m_mapBit.insert({ pImgKey, pMyBmp });
	}
}

HDC CBitmapManager::FindImage(const TCHAR* pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), tagFinder(pImgKey));

	if (iter == m_mapBit.end())
		return nullptr;

	return iter->second->GetMemDC();
}

void CBitmapManager::Release()
{
	for_each(m_mapBit.begin(), m_mapBit.end(), DeleteMap());
	m_mapBit.clear();
}

CBitmapManager::CBitmapManager()
{
}
