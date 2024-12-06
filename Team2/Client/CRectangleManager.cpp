#include "pch.h"
#include "CRectangleManager.h"
#include "CRectangle.h"

CRectangleManager* CRectangleManager::m_pInstance = nullptr;

void CRectangleManager::Initialize()
{
	m_RectList[RECT_NONE].push_back(new CRectangle(0, 500, RECT_NONE));
	m_RectList[RECT_NONE].back()->SetOID(OBJ_RECT);
	m_RectList[RECT_NONE].push_back(new CRectangle(50, 500, RECT_NONE));
	m_RectList[RECT_NONE].back()->SetOID(OBJ_RECT);
	m_RectList[RECT_NONE].push_back(new CRectangle(100, 500, RECT_NONE));
	m_RectList[RECT_NONE].back()->SetOID(OBJ_RECT);
	m_RectList[RECT_NONE].push_back(new CRectangle(150, 500, RECT_NONE));
	m_RectList[RECT_NONE].back()->SetOID(OBJ_RECT);
	m_RectList[RECT_NONE].push_back(new CRectangle(200, 500, RECT_NONE));
	m_RectList[RECT_NONE].back()->SetOID(OBJ_RECT);
	m_RectList[RECT_NONE].push_back(new CRectangle(250, 500, RECT_NONE));
	m_RectList[RECT_NONE].back()->SetOID(OBJ_RECT);
	m_RectList[RECT_NONE].push_back(new CRectangle(300, 500, RECT_NONE));
	m_RectList[RECT_NONE].back()->SetOID(OBJ_RECT);
	m_RectList[RECT_NONE].push_back(new CRectangle(350, 400, RECT_NONE));
	m_RectList[RECT_NONE].back()->SetOID(OBJ_RECT);
	m_RectList[RECT_NONE].push_back(new CRectangle(400, 300, RECT_NONE));
	m_RectList[RECT_NONE].back()->SetOID(OBJ_RECT);


	m_RectList[RECT_NONE].push_back(new CRectangle(50, 350, RECT_NONE));
	m_RectList[RECT_NONE].back()->SetOID(OBJ_RECT);

	m_RectList[RECT_ITEM].push_back(new CRectangle(100, 350, RECT_ITEM));
	m_RectList[RECT_ITEM].back()->SetOID(OBJ_RECT);

	m_RectList[RECT_RANDOM].push_back(new CRectangle(150, 350, RECT_RANDOM));
	m_RectList[RECT_RANDOM].back()->SetOID(OBJ_RECT);

	for (size_t i = 0; i < RECT_END; ++i)
	{
		for (auto& rect : m_RectList[i])
			rect->Initialize();
	}
}

int CRectangleManager::Update()
{
	for (size_t i = 0; i < RECT_END; ++i)
	{
		for (auto iter = m_RectList[i].begin();iter != m_RectList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObject*>(*iter);
				iter = m_RectList[i].erase(iter);
			}
			else
				++iter;
		}
	}
	return 0;
}

void CRectangleManager::Render(HDC hDC)
{
	for (size_t i = 0; i < RECT_END; ++i)
	{
		for (auto& rect : m_RectList[i])
			rect->Render(hDC);
	}
}

void CRectangleManager::Release()
{
}

CRectangleManager::CRectangleManager()
{
}
