#pragma once
#include "MonsterShoot.h"
class MonsterYu :public MonsterShoot
{
public:
	MonsterYu();
	virtual ~MonsterYu();
public:
	virtual void Set_Hp(int _iDamage) override;
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;
public:
	void		Shoot(float _fAngle);
private:
	void Cal_Angle();
	void Pattern1();
	void Pattern2();
	void Pattern3();
	void Pattern4();
};

