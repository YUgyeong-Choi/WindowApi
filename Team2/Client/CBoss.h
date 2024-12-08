#pragma once
#include "CMonster.h"
class CBoss : public CMonster
{
public:
	CBoss();
	virtual ~CBoss() { Release(); }
	virtual void Initialize()		override;
	virtual int  Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC hDC)	override;
	virtual void Release()			override;

	void OnCollision(CObject* _op);
	void OnDead();

public:
	void Pattern1();
	void Pattern2();
	void Pattern3();
	bool CheckOnGround();
	bool CheckPlayer();
	float m_fDistance;
	bool  m_bCanHit;
	float	m_fVelocityX;
	float	m_fVelocityY;
	int		m_iAnimationTime;
	bool	m_bFacingLeft;
};

