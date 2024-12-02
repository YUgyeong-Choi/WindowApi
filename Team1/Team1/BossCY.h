#pragma once
#include "MonsterShoot.h"
class BossCY : public MonsterShoot
{
public:
	BossCY() :m_iTemp(0), m_bMovingPattern{0,}, m_ullMovingTick(GetTickCount64()), m_ullMovingInterval(0) {}
	~BossCY() {}
public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC _hdc) override;

public:
	virtual void    Set_Bullet(list<Obj*>* pBullet) { m_pBulletList = pBullet; }
	void			Set_Hp(int _iDamage);

private:
	enum BOSSMOVE { BOSSMOVESTART,
					ROTATEPAT1, ROTATEPAT2, ROTATEPAT3, ROTATEPAT4,
					FOLLOWPAT,  CENTERPAT,  RETURNPAT,
					BOSSMOVEEND };
	bool			m_bMovingPattern[BOSSMOVEEND];
	int				m_iRotateNum;
	ULONGLONG		m_ullMovingTick;
	ULONGLONG		m_ullMovingInterval;
	float			m_fCenterAngle;
	int				m_iTemp;

private:
	void			MoveBoss(BOSSMOVE	_Type);
	void			BulletPattern(BOSSMOVE	_Type);
	void			FollowPlayer();
	void			MoveToCenter();
};

