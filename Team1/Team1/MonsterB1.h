#pragma once
#include "Monster.h"
class MonsterB1 : public Monster //Monster Bullet One�̶�� ��.. �Ѿ� �ϳ��� �����ٰ�...
{
public:
	MonsterB1();
	~MonsterB1();
public:
	virtual int Update() override;
public:
	virtual void Shoot_Bullet() override;
};

