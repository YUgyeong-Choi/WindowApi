#pragma once
#include "Obj.h"
class Bullet :public Obj
{
public:
	Bullet();
	Bullet(float _fAngle, int _iDamage, int _iObjType) { m_fAngle = _fAngle; m_iDamage = _iDamage; m_iObjType = _iObjType; }
	virtual ~Bullet();
public:
	virtual void Late_Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;
public:
	virtual void Initialize();
	virtual int Update();
protected:
	int m_iObjType;
};

