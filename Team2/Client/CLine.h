#pragma once
#include "Define.h"
class CLine
{
public:
	CLine();
	CLine(Vector<float> _l, Vector<float> _r) : m_LPoint(_l), m_RPoint(_r) {};
	virtual ~CLine() { Release(); }

	virtual void Initialize();
	virtual int  Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
	virtual void Release();

	Vector<float> GetLPoint() { return m_LPoint; }
	Vector<float> GetRPoint() { return m_RPoint; }
private:
	Vector<float> m_LPoint;
	Vector<float> m_RPoint;
};

