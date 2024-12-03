#pragma once
#include "CObj.h"
class Ground :public Obj
{
public:
	Ground();
	Ground(int _fx, int _fy, int _bx, int _by);
	virtual ~Ground();
public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;
public:
	RECT Get_Line() { return m_tLine; }
private:
	RECT m_tLine;
};

