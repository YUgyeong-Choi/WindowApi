#pragma once
#include "MonsterShoot.h"
class BossHero :
    public MonsterShoot
{

public:
	BossHero();
	virtual ~BossHero();
public:
	void ChargePattern();
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hdc) override;
public:
	virtual void Set_Hp(int _iDamage);
	void Set_MonsterList(list<Obj*>* _pMonsterList) { m_pMonsterList = _pMonsterList; }
private:
	bool IsOutMap();
	void CreateThis();
	void Set_Size(float _fCX, float _fCY) { m_tInfo.fCX = _fCX; m_tInfo.fCY = _fCY; }
private:
	enum STATE { IDLE, READY_CHARGE, CHARGE };
	STATE m_eState;
	float m_fCurSpeed;
	float m_fChargeAngle;
	ULONGLONG ullLastStateChange_Time;
	POINT m_tChargePos;

	list<Obj*>* m_pMonsterList;
};

