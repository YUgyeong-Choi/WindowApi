#pragma once
#include "Define.h"
class CObject
{
public:
	CObject();
	virtual ~CObject();
public:
	virtual void		Initialize() PURE;
	virtual int		Update() PURE;
	virtual void		Late_Update() PURE;
	virtual void		Render(HDC _hDC) PURE;
	virtual void		Release() PURE;
public:
	void		Update_Rect();
protected:
	INFO		m_tInfo;
	RECT		m_tRect;

	float		m_fSpeed;
	float		m_fAngle;

	bool		m_bDead;

	CObject* m_pTarget;
};

