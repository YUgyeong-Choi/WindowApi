#pragma once
#include "CMonster.h"
class CMonsterYK1 :public CMonster
{
public:
	CMonsterYK1() {};
	virtual ~CMonsterYK1() { Release(); }
	virtual void Initialize() override;
	virtual int  Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void OnCollision(CObject* _op);
	virtual void OnDead();
};

