#include "pch.h"
#include "CPlayer.h"

Player::Player() :m_tInfo({}), m_tRect({}), m_fSpeed(0), m_tGround({}), m_Angle(0), checkEnd()
{
}

Player::~Player()
{
	Release();
}

void Player::Initialize()
{
	m_tInfo = { 100, 400, 50.f, 50.f };
	m_fSpeed = 1.f;
	Cal_Angle(RIGHT);
}

void Player::Update()
{
	Key_Input();
	Update_Rect();
}

void Player::Late_Update()
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
	if (GetAsyncKeyState('A')) {
		m_tInfo.fX -= m_fSpeed;
		m_tInfo.fY = m_Angle * (m_tInfo.fX - m_tGround.right) + m_tGround.bottom;
		End_LeftLine();
	}

	if (GetAsyncKeyState('D')) {
		m_tInfo.fX += m_fSpeed;
		m_tInfo.fY = m_Angle * (m_tInfo.fX - m_tGround.right) + m_tGround.bottom;
		End_RightLine();
	}
}

void Player::Update_Rect()
{
	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}

void Player::Cal_Angle(int _dir)
{
	switch (_dir)
	{
	case LEFT:
		m_Angle = (m_tInfo.fY - m_tGround.top) / (m_tInfo.fX - m_tGround.left);
		break;
	case RIGHT:
		m_Angle = (m_tInfo.fY - m_tGround.bottom) / (m_tInfo.fX - m_tGround.right);
		break;
	case DIR_END:
		break;
	default:
		break;
	}
}

void Player::End_LeftLine()
{
	if (m_tGround.left == m_tInfo.fX && m_tGround.top == m_tInfo.fY) {
		checkEnd[LEFT] = true;
	}
	else {
		checkEnd[LEFT] = false;
	}
}

void Player::End_RightLine()
{
	if (m_tGround.right == m_tInfo.fX && m_tGround.bottom == m_tInfo.fY) {
		checkEnd[RIGHT] = true;
	}
	else {
		checkEnd[RIGHT] = false;
	}
}
