#pragma once
#include "Define.h"
class Obj
{
public:
	Obj();
	virtual ~Obj();
public:
	const RECT* Get_Rect() { return &m_tRect; }
	INFO Get_Info() { return m_tInfo; }
	void		Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	int Get_Hp() { return m_iHp; }
	int Get_Damage() { return m_iDamage; }
	void Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void Set_Target(Obj* pTarget) { m_pTarget = pTarget; }
	void Set_Hp(int _iDamage);
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
	Obj* m_pTarget;

	bool		m_bDead;
	int			m_iHp;
	int			m_iDamage;

};

