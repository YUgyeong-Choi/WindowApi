#pragma once
#include "Obj.h"
class Bullet :public Obj
{
public:
	Bullet();
	Bullet(Direction _dir) { m_dir = _dir; }
	~Bullet();
public:
	void Initialize() override;
	void Update() override;
	void Render(HDC _hdc) override;
	void Release() override;
public:
	bool CheckOut();
private:
	Direction m_dir;
};

