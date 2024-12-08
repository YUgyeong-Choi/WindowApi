#pragma once
#include "CObject.h"
class CProjectile : public CObject
{
public:
	CProjectile();
	virtual ~CProjectile() { Release(); }
	virtual void Initialize() override;
	virtual int  Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	virtual void OnCollision(CObject* _op);
	virtual void OnDead();
public:
	bool	CheckBoundary();
	void		Jump();
	OBJID m_eOwner;
};

