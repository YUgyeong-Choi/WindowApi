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
	void Initialize() override;
	void Update() override;
	void Render(HDC _hdc) override;
	void Release() override;
private:
	void Key_Input();
	Obj* Create_Bullet(float radian);
private:
	bool bKeyPressed[4];
	list<Obj*>* m_BulletList;
};

