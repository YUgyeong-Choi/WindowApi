#pragma once
#include "Monster.h"
class MonsterB1 : public Monster //Monster Bullet One이라는 뜻.. 총알 하나만 보낸다고...
{
public:
	MonsterB1();
	~MonsterB1();
public:
	virtual int Update() override;
public:
	virtual void Shoot_Bullet() override;
};

