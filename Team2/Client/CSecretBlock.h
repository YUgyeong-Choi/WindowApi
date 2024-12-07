#pragma once
#include "CBlock.h"
class CSecretBlock : public CBlock
{
public:
	CSecretBlock();
	virtual ~CSecretBlock() { Release(); }

	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void OnCollision(CObject* _op);
	virtual void OnDead();
private:
	bool m_bActive;
};

