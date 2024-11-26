#include "Player.h"
#include "Bullet.h"

Player::Player()
{
}

Player::~Player()
{
	Release();
}

void Player::Initialize()
{
	m_tInfo = { WINCX / 2.f, WINCY / 2.f, 15.f, 15.f };
	m_fSpeed = 5.f;
}

void Player::Update()
{
	Key_Input();
	Obj::Update_Rect();
}

void Player::Render(HDC _hdc)
{
	Rectangle(_hdc,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void Player::Release()
{
}

void Player::Key_Input()
{
	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
	}

	if (GetAsyncKeyState(VK_UP))
	{
		m_tInfo.fY -= m_fSpeed;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		m_tInfo.fY += m_fSpeed;
	}

	if (GetAsyncKeyState('w'))
	{
		m_BulletList->push_back(Create_Bullet(BulletDirection::UP));
	}

	if (GetAsyncKeyState('s'))
	{
		m_BulletList->push_back(Create_Bullet(BulletDirection::DOWN));
	}

	if (GetAsyncKeyState('a'))
	{
		m_BulletList->push_back(Create_Bullet(BulletDirection::LEFT));
	}

	if (GetAsyncKeyState('d'))
	{
		m_BulletList->push_back(Create_Bullet(BulletDirection::RIGHT));
	}
}

Obj* Player::Create_Bullet(BulletDirection _dir)
{
	Obj* pBullet = new Bullet(_dir);

	pBullet->Initialize();
	pBullet->Set_Pos(m_tInfo.fX, m_tInfo.fY);

	return pBullet;
}

