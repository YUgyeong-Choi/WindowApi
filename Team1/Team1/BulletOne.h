#pragma once
#include "Bullet.h"
class BulletOne :public Bullet
{
public:
	BulletOne();
	BulletOne(float _fAngle, int _iDamage, int _iObjType) { m_fAngle = _fAngle; m_iDamage = _iDamage; m_iObjType = _iObjType; }
	virtual ~BulletOne();
public:
	virtual void Initialize() override;
	virtual int Update() override;
};

