#pragma once
#include "Define.h"
class Obj
{
public:
	Obj();
	virtual ~Obj();
public:
	virtual void Initialize();
	virtual void Update();
	virtual void Late_Update();
	virtual void Render(HDC _hdc);
	virtual void Release();
};

