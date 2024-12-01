#pragma once
#include "Obj.h"
class Monster :public Obj
{
public: 
	Monster();
	virtual ~Monster();
public:
	void        Set_Bullet(list<Obj*>* pBullet) { m_pBulletList = pBullet; }
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;
protected:
	void Calc_Angle();
	Obj* Create_Bullet(float _fAngle);
	Obj* Create_BulletScrew(float _fAngle);
	virtual void Shoot_Bullet();
protected:
	list<Obj*>* m_pBulletList;
	int m_iDir;

	int m_iFireRate; //총알 발사 속도
	int m_iTick;
	int m_BulletDamage;
};

