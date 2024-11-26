#pragma once
#include "Obj.h"
#include "pch.h"
class Monster :public Obj
{
public:
	Monster();
	Monster(Direction _dir);
	~Monster();
public:
	void Initialize() override;
	void Update() override;
	void Render(HDC _hdc) override;
	void Release() override;
public:
	bool CheckHit(list<Obj*> m_BulletList);
private:
	Direction m_dir;
};
