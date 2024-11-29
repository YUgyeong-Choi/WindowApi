#pragma once
#include "Item.h"
class ShieldItem :public Item
{
public:
	ShieldItem();
	virtual ~ShieldItem();
public:
	virtual void Render(HDC _hdc) override;
	virtual void UseITem() override;
};

