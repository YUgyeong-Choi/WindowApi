#pragma once
#include "Item.h"
class ShootSpeedItem :public Item
{
public:
	ShootSpeedItem();
	~ShootSpeedItem();
public:
	virtual void Render(HDC _hdc) override;
	virtual void UseITem() override;
};

