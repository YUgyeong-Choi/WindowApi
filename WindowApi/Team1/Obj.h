#pragma once
#include "Define.h"
class Obj
{
public:
	Obj();
	virtual ~Obj();
public:
	RECT Get_Rect() { return m_tRect; }
	INFO Get_Info() { return m_tInfo; }
public:
	virtual void Initialize() PURE;
	virtual int Update() PURE;
	virtual void Late_Update() PURE;
	virtual void Render(HDC _hdc) PURE;
	virtual void Release() PURE;
public:
	void		Update_Rect();
protected:
	INFO		m_tInfo;
	RECT		m_tRect;

	float		m_fAngle;
	float		m_fSpeed;
	float		m_fDistance;

	bool		m_bDead;
};

