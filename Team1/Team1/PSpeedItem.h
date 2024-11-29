#pragma once
#include "Item.h"
class PSpeedItem :public Item
{
public:
	PSpeedItem();
	virtual ~PSpeedItem();
public:
	virtual void Render(HDC _hdc) override;
	virtual void UseITem() override;
};

