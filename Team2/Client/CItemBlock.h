#pragma once
#include "CBlock.h"
class CItemBlock : public CBlock
{
public:
	CItemBlock();
	virtual ~CItemBlock() { Release(); }

	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void OnCollision(CObject* _op);
	virtual void OnDead();
private:
	bool m_bActive;
};

