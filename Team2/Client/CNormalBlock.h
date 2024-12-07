#pragma once
#include "CBlock.h"
class CNormalBlock : public CBlock
{
public:
	CNormalBlock();
	virtual ~CNormalBlock() { Release(); }
	virtual void Initialize();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void OnCollision(CObject* _op);
	virtual void OnDead();
};

