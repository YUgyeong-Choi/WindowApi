#include "pch.h"
#include "PSpeedItem.h"

PSpeedItem::PSpeedItem()
{
}

PSpeedItem::~PSpeedItem()
{
}

void PSpeedItem::Render(HDC _hdc)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(247, 230, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, myBrush);
	Ellipse(_hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(_hdc, oldBrush);
	DeleteObject(myBrush);
}

void PSpeedItem::UseITem()
{
	static_cast<Player*>(m_pTarget)->Set_PSpeed(2);
}
