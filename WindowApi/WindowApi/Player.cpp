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

	bKeyPressed.push_back(false);
	bKeyPressed.push_back(false);
	bKeyPressed.push_back(false);
	bKeyPressed.push_back(false);
}

void Player::Update()
{
	Key_Input();
	Obj::Update_Rect();
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
			m_tInfo.fY += m_fSpeed;
		}
	}

	if (GetAsyncKeyState('A'))
	{
		if (!bKeyPressed[Direction::LEFT]) {
			m_BulletList->push_back(Create_Bullet(Direction::LEFT));
			bKeyPressed[Direction::LEFT] = true;
		}
	}
	else {
		bKeyPressed[Direction::LEFT] = false;
	}

	if (GetAsyncKeyState('W'))
	{
		if (!bKeyPressed[Direction::UP]) {
			m_BulletList->push_back(Create_Bullet(Direction::UP));
			bKeyPressed[Direction::UP] = true;
		}
	}
	else {
		bKeyPressed[Direction::UP] = false;
	}

	if (GetAsyncKeyState('D'))
	{
		if (!bKeyPressed[Direction::RIGHT]) {
			m_BulletList->push_back(Create_Bullet(Direction::RIGHT));
			bKeyPressed[Direction::RIGHT] = true;
		}
	}
	else {
		bKeyPressed[Direction::RIGHT] = false;
	}

	if (GetAsyncKeyState('S'))
	{
		if (!bKeyPressed[Direction::DOWN]) {
			m_BulletList->push_back(Create_Bullet(Direction::DOWN));
			bKeyPressed[Direction::DOWN] = true;
		}
	}
	else {
		bKeyPressed[Direction::DOWN] = false;
	}
}

Obj* Player::Create_Bullet(Direction _dir)
{
	Obj* pBullet = new Bullet(_dir);

	pBullet->Initialize();
	pBullet->Set_Pos(m_tInfo.fX, m_tInfo.fY);

	return pBullet;
}

