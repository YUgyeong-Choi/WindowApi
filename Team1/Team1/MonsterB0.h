#pragma once
#include "Monster.h"
class MonsterB0 :public Monster //���� bullter 0, �߻���Ѵٴ� ��..
{
public:
	MonsterB0();
	~MonsterB0();
public:
	virtual int Update() override;
public:
	virtual void Shoot_Bullet() override;
};

