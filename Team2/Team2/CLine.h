#pragma once
#include "Define.h"

class CLine
{
public:
	CLine();
	CLine(LINEPOINT& tLeft, LINEPOINT& tRight);
	CLine(LINE& tLine);
	~CLine();
public:
	LINE Get_Info() { return m_tInfo; }

public:
	void		Render(HDC _hDC);

private:
	LINE		m_tInfo;
};