#pragma once
#include "Item.h"
class HealItem :public Item
{
public:
	HealItem();
	virtual ~HealItem();
public:
	virtual void Render(HDC _hdc) override;
	virtual void UseITem() override;
};

