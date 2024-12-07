#pragma once
#include "CBlock.h"
class CBreakBlock : public CBlock
{
public:
	CBreakBlock();
	virtual ~CBreakBlock() { Release(); }

	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void OnCollision(CObject* _op);
	virtual void OnDead();
};

