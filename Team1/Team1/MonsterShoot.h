#pragma once
#include "Monster.h"

class MonsterShoot : public Monster
{
public:
	MonsterShoot();
	~MonsterShoot();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;

private:
	list<Obj*>* m_pBulletList;

public:
	Obj* Create_Bullet();
	void        Set_Bullet(list<Obj*>* pBullet) { m_pBulletList = pBullet; }
	void		Shoot();
};

