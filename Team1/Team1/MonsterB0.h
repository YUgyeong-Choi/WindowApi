#pragma once
#include "Monster.h"
class MonsterB0 :public Monster //몬스터 bullter 0, 발사안한다는 뜻..
{
public:
	MonsterB0();
	~MonsterB0();
public:
	virtual int Update() override;
public:
	virtual void Shoot_Bullet() override;
};

