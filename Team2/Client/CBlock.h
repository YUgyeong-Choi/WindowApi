#pragma once
#include "CObject.h"
#include "Define.h"
class CBlock : public CObject
{
public:
	CBlock();
	virtual ~CBlock() { Release(); }

	virtual void Initialize();
	virtual int  Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void OnCollision(CObject* _op);
	virtual void OnDead();
protected:
	RECTANGLETYPE m_RectType;
};


