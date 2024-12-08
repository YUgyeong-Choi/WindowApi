#pragma once
#include "CProjectile.h"

class CPlayerBullet : public CProjectile
{
public:
	CPlayerBullet();
	~CPlayerBullet() { Release(); }

	virtual void Initialize() override;
	virtual int  Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	virtual void OnCollision(CObject* _op)override;
	virtual void OnDead();
};

