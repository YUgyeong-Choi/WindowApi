#include "pch.h"
#include "CGround.h"

Ground::Ground():m_tLine({})
{
}

Ground::Ground(int _fx, int _fy, int _bx, int _by)
{
	//m_tLine 여기서 Rect의 fx,fy는 왼쪽 좌표, bx by는 오른쪽 좌표를 의미 
	m_tLine.left = _fx;
	m_tLine.top = _fy;
	m_tLine.right = _bx;
	m_tLine.bottom = _by;
}

Ground::~Ground()
{
	Release();
}

void Ground::Initialize()
{
}

void Ground::Update()
{
}

void Ground::Late_Update()
{
}

void Ground::Render(HDC _hdc)
{
	MoveToEx(_hdc, m_tLine.left, m_tLine.top, nullptr);
	LineTo(_hdc, m_tLine.right, m_tLine.bottom);
}

void Ground::Release()
{
}
