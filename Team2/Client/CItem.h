#pragma once
#include "CObject.h"
class CItem : public CObject
{
public:
	CItem();
	virtual ~CItem() { Release(); }
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

