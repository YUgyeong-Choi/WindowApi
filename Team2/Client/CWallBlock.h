#pragma once
#include "CBlock.h"
class CWallBlock :public CBlock
{
public:
	CWallBlock();
	virtual ~CWallBlock() { Release(); }

	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void OnCollision(CObject* _op);
	virtual void OnDead();
};

