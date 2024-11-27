#pragma once
#include "Obj.h"
class Bullet :public Obj
{
public:
	Bullet();
	Bullet(DIR _dir) { m_dir = _dir; }
	~Bullet();
public:
	void Initialize() override;
	int Update() override;
	void LateUpdate() override;
	void Render(HDC _hdc) override;
	void Release() override;
private:
	DIR m_dir;
};

