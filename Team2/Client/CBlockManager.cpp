#include "pch.h"
#include "CBlockManager.h"
#include "CBlock.h"
#include "CBlockItem.h"
#include "CBlockBroken.h"
#include "CBlockHard.h"
#include "CAbstractFactory.h"

CBlockManager* CBlockManager::m_pInstance(nullptr);

void CBlockManager::Initialize()
{
	for (int i = 0; i < 30; i++)
	{
		m_BlockList[BLOCK_HARD].push_back(CAbstractFactory<CBlockHard>::Create(-100.f + i * 50.f, WINCY - 50.f));
	}

	m_BlockList[BLOCK_NONE].push_back(CAbstractFactory<CBlockBroken>::Create(WINCX - 100, WINCY - 250));
	m_BlockList[BLOCK_ITEM].push_back(CAbstractFactory<CBlockItem>::Create(WINCX - 200, WINCY - 250));
	m_BlockList[BLOCK_HARD].push_back(CAbstractFactory<CBlockHard>::Create(WINCX - 300, WINCY - 250));
}

int CBlockManager::Update()
{
	POINT ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	for (int i = 0; i < BLOCK_END; i++)
	{
		for (auto iter = m_BlockList[i].begin();
			iter != m_BlockList[i].end(); )
		{
			int iResult = (*iter)->Update();
			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObject*>(*iter);
				iter = m_BlockList[i].erase(iter);
			}
			else
				iter++;
		}
	}

	return 0;
}

void CBlockManager::LateUpdate()
{
}

void CBlockManager::Render(HDC hDC)
{
	for (int i = 0; i < BLOCK_END; i++)
	{
		for (auto& pBlock : m_BlockList[i])
			pBlock->Render(hDC);
	}
}

void CBlockManager::Release()
{
	for (int i = 0; i < BLOCK_END; i++)
	{
		for_each(m_BlockList[i].begin(), m_BlockList[i].end(), Safe_Delete<CObject*>);
		m_BlockList[i].clear();
	}
}

CBlockManager::CBlockManager()
{
}

CBlockManager::~CBlockManager()
{
	Release();
}
