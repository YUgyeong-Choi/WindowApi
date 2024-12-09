#pragma once
#include "CMonster.h"
class CMonsterYK2 :public CMonster
{
public:
	CMonsterYK2();
	virtual ~CMonsterYK2() { Release(); }
	virtual void Initialize() override;
	virtual int  Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void OnCollision(CObject* _op);
	virtual void OnDead();
private:
	void Fire();
private:
	float m_fDeadTime;
	int m_iFireRate;
	int m_iFireTick;
};

