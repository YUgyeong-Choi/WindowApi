#pragma once
#include "CMonster.h"
class CMonsterBossYK : public CMonster
{
public:
	CMonsterBossYK();
	virtual ~CMonsterBossYK() { Release(); }
	virtual void Initialize() override;
	virtual int  Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void OnCollision(CObject* _op);
	virtual void OnDead();
private:
	void Pattern1();
	void Pattern2();
private:
	int m_iDamageRate; //µ¥¹ÌÁö Æ½
	int m_iTick;
	bool m_isCanDamage;
	int m_PatternRate;
	int m_PatternTick;
	int m_iPattern;
	int m_iPatternCycle;
	int m_iFireRate; //ÃÑ¾Ë ¹ß»ç ¼Óµµ
	int m_iFireTick;
};

