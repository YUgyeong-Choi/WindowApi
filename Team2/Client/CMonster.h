#pragma once
#include "CObject.h"
class CMonster : public CObject
{
public:
	CMonster() {};
	virtual ~CMonster() { Release(); }
	virtual void Initialize() override;
	virtual int  Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void OnCollision(CObject* _op);
	virtual void OnDead();

	bool FindPlayer();
};

