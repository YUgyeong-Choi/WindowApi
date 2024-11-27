#pragma once
#include "Obj.h"
#include "pch.h"
class Monster :public Obj
{
public:
	Monster();
	Monster(DIR _dir);
	~Monster();
public:
	void Initialize() override;
	int Update() override;
	void LateUpdate() override;
	void Render(HDC _hdc) override;
	void Release() override;
private:
	DIR m_dir;
};
