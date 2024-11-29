#pragma once
#include "Item.h"
class BulletItem :public Item
{
public:
	BulletItem();
	virtual ~BulletItem();
public:
	virtual void Render(HDC _hdc) override;
	virtual void UseITem() override;
};

