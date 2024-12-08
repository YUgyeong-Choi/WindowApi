#pragma once
#include "CBlock.h"

class CBlockManager
{
public:
	void Initialize();
	int  Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();

	list<CObject*>* GetList() { return m_BlockList; } // OBJManager에서 충돌시키기 위한 겟 리스트

	static CBlockManager* GetInstance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CBlockManager;

		return m_pInstance;
	}

	static void DestroyInstance()
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	CBlockManager();
	CBlockManager(CBlockManager& _rhs) = delete;
	CBlockManager operator =(CBlockManager& rCBlockManager) = delete;
	~CBlockManager();

	static CBlockManager* m_pInstance;

	list<CObject*> m_BlockList[BLOCK_END];
};

