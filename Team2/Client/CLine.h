#pragma once
#include "../Client/Define.h"
class CLine
{
public:
	CLine();
	CLine(Vector<float> _l, Vector<float> _r) : m_LPoint(_l), m_RPoint(_r) {};
	CLine(LINEPOINT& tLeft, LINEPOINT& tRight);
	CLine(LINE& tInfo);
	virtual ~CLine() { Release(); }

	virtual void Initialize();
	virtual int  Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();

	void ScrollOffset();

	Vector<float> GetLPoint() { return m_LPoint; }
	Vector<float> GetRPoint() { return m_RPoint; }
	const LINE*		GetInfo() { return &m_tInfo; }
	float		  GetCurrentY(float _fX);

private:

	Vector<float> m_LPoint;
	Vector<float> m_RPoint;
	LINE		m_tInfo;
	float		m_fSpeed;
};

