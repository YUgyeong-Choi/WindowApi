#include "pch.h"
#include "Satellite.h"

Satellite::Satellite()
{
}

Satellite::~Satellite()
{
	Release();
}

void Satellite::Initialize()
{
	m_tInfo.fCX = 15.f;
	m_tInfo.fCY = 15.f;
	m_fDistance = 30.f;
	m_fSpeed = 5.f;
}

int Satellite::Update()
{
	m_fAngle += m_fSpeed;
	m_tInfo.fX = long(m_tInfo.fX + (m_fDistance * cosf(m_fAngle * (PI / 180.f))));
	m_tInfo.fY = long(m_tInfo.fY - (m_fDistance * sinf(m_fAngle * (PI / 180.f))));

	Obj::Update_Rect();
	return OBJ_NOEVENT;
}

void Satellite::Late_Update()
{
}

void Satellite::Render(HDC _hdc)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(247, 230, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, myBrush);
	Ellipse(_hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(_hdc, oldBrush);
	DeleteObject(myBrush);
}

void Satellite::Release()
{
}