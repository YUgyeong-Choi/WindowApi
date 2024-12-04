#pragma once
#include "CObj.h"
class Player:public Obj
{
public:
	Player();
	virtual ~Player();
public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;
public:
	INFO Get_Info() { return m_tInfo; }
	void Set_Line(RECT _line) { m_tGround = _line; }
	void Cal_Angle(int _dir);
	bool* Get_End() { return m_bCheckEnd; }
	void Set_Out() { m_bCheckOut = true; }
private:
	void		Key_Input();
	void		Update_Rect();
	void		End_LeftLine();
	void		End_RightLine();
private:
	RECT m_tRect;
	INFO m_tInfo;
	float m_fSpeed;

	RECT m_tGround;
	float m_Angle; //±â¿ï±â
	bool m_bCheckEnd[DIR_END];
	bool m_bCheckOut;
};

