#include "pch.h"
#include "HealItem.h"

HealItem::HealItem()
{
}

HealItem::~HealItem()
{
}

void HealItem::Render(HDC _hdc)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 153, 0)); //ÃÊ·Ï»ö
	HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, myBrush);
	Ellipse(_hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(_hdc, oldBrush);
	DeleteObject(myBrush);
}

void HealItem::UseITem()
{
	static_cast<Player*>(m_pTarget)->Set_Hp(10);
}
