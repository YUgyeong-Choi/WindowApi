#include "pch.h"
#include "ShieldItem.h"

ShieldItem::ShieldItem()
{
}

ShieldItem::~ShieldItem()
{
}

void ShieldItem::Render(HDC _hdc)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 192, 203));
	HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, myBrush);
	Ellipse(_hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(_hdc, oldBrush);
	DeleteObject(myBrush);
}

void ShieldItem::UseITem()
{
	static_cast<Player*>(m_pTarget)->Add_Shield();
}
