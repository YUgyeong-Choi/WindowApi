#include "pch.h"
#include "CGround.h"

Ground::Ground():m_tLine({})
{
}

Ground::Ground(int _fx, int _fy, int _bx, int _by)
{
	//m_tLine ���⼭ Rect�� fx,fy�� ���� ��ǥ, bx by�� ������ ��ǥ�� �ǹ� 
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
