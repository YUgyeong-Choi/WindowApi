#pragma once
#include "CObject.h"
#include "Define.h"
#include "CScrollManager.h"

class CBlock : public CObject
{
public:
	CBlock();

public:
	BLOCKTYPE GetBlockType()
	{
		return m_BlockType;
	}
	void SetBlockType(BLOCKTYPE _type)
	{
		m_BlockType = _type;
	}

protected:
	BLOCKTYPE m_BlockType;

	// CObject��(��) ���� ��ӵ�
	void Initialize() override;
	int Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;
};
