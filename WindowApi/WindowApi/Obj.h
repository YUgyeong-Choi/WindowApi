#pragma once
#include "Define.h"

class Obj
{
public:
	Obj();
	virtual ~Obj();
public:
	const RECT* Get_Rect() { return &m_tRect; }
	INFO Get_INFO() { return m_tInfo; }
	void		Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
public:
	virtual void Initialize() PURE;
	virtual int Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render(HDC _hdc) PURE;
	virtual void Release() PURE;
public:
	void		Update_Rect();
	void SetDead() { m_bDead = true; }
protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	bool		m_bDead;
	float		m_fSpeed;
};

