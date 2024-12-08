#pragma once
#include "CObject.h"
#include "Define.h"
#include "CScrollManager.h"

class CBlock : public CObject
{
public:
	CBlock();
	virtual ~CBlock() {};

	

public:
	BLOCKTYPE GetBlockType(){ return m_BlockType;}

	void SetBlockType(BLOCKTYPE _bt) { m_BlockType = _bt; }
protected:
	BLOCKTYPE m_BlockType;

	// CObject을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;
};

