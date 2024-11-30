#pragma once
#include "Bullet.h"
class BulletScrew :public Bullet
{
public:
	BulletScrew();
	BulletScrew(float _fAngle);
	virtual ~BulletScrew();
public:
	virtual void Initialize() override;
    virtual int Update() override;
private:
	POINT			m_tCenter;

	float			m_fRotAngle;
	float			m_fRotSpeed;

	bool			m_bStart;
};

