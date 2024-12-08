#pragma once
#include "CObject.h"

class CMonsterKL : public CObject
{
public:
	CMonsterKL() : m_bCollision(false) {};
	virtual ~CMonsterKL() { Release(); }
	virtual void Initialize() override;
	virtual int  Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void OnCollision(CObject* _op);
	virtual void OnDead();
	void		 SelectAction();
	void		 SelectStatus();

private:
	bool		m_bCollision;
};

