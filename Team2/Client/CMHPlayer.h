#pragma once
#include "../Client/CPlayer.h"
class CMHPlayer : public CPlayer
{

public:
	CMHPlayer();
	virtual ~CMHPlayer() { Release(); }
	virtual void Initialize()		override;
	virtual int  Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC hDC)	override;
	virtual void Release()			override;

	virtual void Jump();
	virtual void KeyInput();


	virtual void OnCollision(CObject* _op);
	virtual void OnDead();
	void		 ScrollOffset();
	bool		 CheckOnGround();
	void		 OnMushroom();
	void		 OnFlower();
	void		 Fire();
public:
	POINT	m_PHead;
	float	m_fVelocityX;
	float	m_fVelocityY;
	int		m_iAnimationTime;
	bool	m_bFacingLeft;
	ULONG64 m_ullLastFire;
	ULONG64 m_ullFireDelay;
};

