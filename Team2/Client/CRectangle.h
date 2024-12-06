#pragma once
#include "CObject.h"
#include "Define.h"
class CRectangle : public CObject
{
public:
	CRectangle();
	CRectangle(float _fX, float _fY, RECTANGLETYPE _type);
	virtual ~CRectangle() { Release(); }

	virtual void Initialize();
	virtual int  Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();
	virtual void OnCollision(CObject* _op);
	virtual void OnDead();
private:
	RECTANGLETYPE m_RectType;
};


