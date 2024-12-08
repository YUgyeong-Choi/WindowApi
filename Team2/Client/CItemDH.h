#pragma once
#include "CObject.h"
class CItemDH : public CObject
{
public:
	CItemDH();
	virtual ~CItemDH() { Release(); }
	virtual void Initialize() override;
	virtual int  Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
protected:
	virtual void OnCollision(CObject* _op);
	virtual void OnDead();
private:

};

