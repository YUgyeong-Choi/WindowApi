#pragma once
#include "CItem.h"

class CFlower : public CItem
{
public:
	CFlower();
	~CFlower();
	virtual void Render(HDC hDC) override;
	virtual void OnCollision(CObject* _op);
private:

};