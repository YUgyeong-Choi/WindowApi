#pragma once
#include "Obj.h"
#include "pch.h"

class Player: public Obj
{
public:
	Player();
	~Player();
public:
	void        Set_Bullet(list<Obj*>* pBullet) { m_BulletList = pBullet; }

public:
	void Initialize() override;
	int Update() override;
	void LateUpdate() override;
	void Render(HDC _hdc) override;
	void Release() override;
private:
	void Key_Input();
	Obj* Create_Bullet(DIR _dir);
private:
	bool bKeyPressed[DIR::NONE];
 	list<Obj*>* m_BulletList;
};

