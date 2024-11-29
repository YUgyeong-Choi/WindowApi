#pragma once
#include "Obj.h"
class Bullet :public Obj
{
public:
	Bullet();
	Bullet(float _fAngle) { m_fAngle = _fAngle; }
	virtual ~Bullet();
public:
	virtual void Late_Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;
public:

	virtual void Initialize() PURE;
	virtual int Update() PURE;
};

