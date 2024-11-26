#pragma once
#include "Define.h"

class Obj
{
public:
	Obj();
	virtual ~Obj();
public:
	void		Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
public:
	virtual void Initialize() PURE;
	virtual void Update() PURE;
	virtual void Render(HDC _hdc) PURE;
	virtual void Release() PURE;
public:
	void		Update_Rect();
protected:
	INFO		m_tInfo; //���� & ������
	RECT		m_tRect; //���� �׸��� ���� ��ǥ
	float		m_fSpeed;
};

