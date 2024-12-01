#pragma once
#include "MonsterShoot.h"
class MonsterYu :public MonsterShoot
{
public:
	MonsterYu();
	virtual ~MonsterYu();
public:
	virtual void Set_Hp(int _iDamage) override;
	void        Set_Monster(list<Obj*>* pMonster) { m_pMonsterList = pMonster; }
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;
public:
	void		Shoot(float _fAngle);
private:
	float Cal_Angle(float _x, float _y);
	void Pattern1();
	void Pattern2();
	void Pattern3();
	void Pattern4();
	void SpawnMonster(float _x, float _y);
private:
	enum PATTERNTYPE{RAIN, MISSILE, BABY, CIRCLE, NONE };
private:
	int m_iPatternCycle;
	int m_iPattern;
	int m_iShootRate;
	list<Obj*>* m_pMonsterList;
};

