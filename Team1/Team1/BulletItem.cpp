#include "pch.h"
#include "BulletItem.h"

BulletItem::BulletItem()
{
}

BulletItem::~BulletItem()
{
}


void BulletItem::Render(HDC _hdc)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(111, 79, 40));
	HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, myBrush);
	Ellipse(_hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(_hdc, oldBrush);
	DeleteObject(myBrush);
}

void BulletItem::UseITem()
{
	static_cast<Player*>(m_pTarget)->Upgrade_Bullet();
}
