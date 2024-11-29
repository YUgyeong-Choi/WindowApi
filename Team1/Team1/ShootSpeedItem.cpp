#include "pch.h"
#include "ShootSpeedItem.h"

ShootSpeedItem::ShootSpeedItem()
{
}

ShootSpeedItem::~ShootSpeedItem()
{
}

void ShootSpeedItem::Render(HDC _hdc)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(139, 119, 173));
	HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, myBrush);
	Ellipse(_hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(_hdc, oldBrush);
	DeleteObject(myBrush);
}

void ShootSpeedItem::UseITem()
{
	static_cast<Player*>(m_pTarget)->Set_SSpeed(1);
}
