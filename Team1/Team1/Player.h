#pragma once
#include "Obj.h"
class Player : public Obj
{
public:
	Player();
	~Player();
public:
	void        Set_Bullet(list<Obj*>* pBullet) { m_BulletList = pBullet; }

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;
private:
	void Key_Input();
	void Calc_Angle();
	Obj* Create_Bullet(float radian);
private:
	bool bKeyPressed;
	list<Obj*>* m_BulletList;
	POINT m_tPosin;
};

