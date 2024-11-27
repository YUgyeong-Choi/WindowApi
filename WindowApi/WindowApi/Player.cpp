#include "Player.h"
#include "Bullet.h"

Player::Player():m_BulletList(nullptr)
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

int Player::Update()
{
	Key_Input();
	Obj::Update_Rect();

	return OBJ_NOEVENT;
}

void Player::LateUpdate()
{
}

void Player::Render(HDC _hdc)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 153, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, myBrush);
	Rectangle(_hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(_hdc, oldBrush);
	DeleteObject(myBrush);
}

void Player::Release()
{
}

void Player::Key_Input()
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
		if (100 >= LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f))) {
			m_tInfo.fX += m_fSpeed;
		}
	}

	if (GetAsyncKeyState(VK_UP))
	{
		m_tInfo.fY -= m_fSpeed;
		if (100 >= LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f))) {
			m_tInfo.fY += m_fSpeed;
		}
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
		if (WINCX - 100 <= LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f))) {
			m_tInfo.fX -= m_fSpeed;
		}
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		m_tInfo.fY += m_fSpeed;
		if (WINCY - 100 <= LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f))) {
			m_tInfo.fY -= m_fSpeed;
		}
	}

	if (GetAsyncKeyState('A'))
	{
		if (!bKeyPressed[DIR::LEFT]) {
			m_BulletList->push_back(Create_Bullet(DIR::LEFT));
			bKeyPressed[DIR::LEFT] = true;
		}
	}
	else {
		bKeyPressed[DIR::LEFT] = false;
	}

	if (GetAsyncKeyState('W'))
	{
		if (!bKeyPressed[DIR::UP]) {
			m_BulletList->push_back(Create_Bullet(DIR::UP));
			bKeyPressed[DIR::UP] = true;
		}
	}
	else {
		bKeyPressed[DIR::UP] = false;
	}

	if (GetAsyncKeyState('D'))
	{
		if (!bKeyPressed[DIR::RIGHT]) {
			m_BulletList->push_back(Create_Bullet(DIR::RIGHT));
			bKeyPressed[DIR::RIGHT] = true;
		}
	}
	else {
		bKeyPressed[DIR::RIGHT] = false;
	}

	if (GetAsyncKeyState('S'))
	{
		if (!bKeyPressed[DIR::DOWN]) {
			m_BulletList->push_back(Create_Bullet(DIR::DOWN));
			bKeyPressed[DIR::DOWN] = true;
		}
	}
	else {
		bKeyPressed[DIR::DOWN] = false;
	}
}

Obj* Player::Create_Bullet(DIR _dir)
{
	Obj* pBullet = new Bullet(_dir);

	pBullet->Initialize();
	pBullet->Set_Pos(m_tInfo.fX, m_tInfo.fY);

	return pBullet;
}

