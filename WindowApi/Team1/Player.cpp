#include "pch.h"
#include "Player.h"

Player::Player() : bKeyPressed(false)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	m_tInfo = { WINCX / 2.f, WINCY / 2.f, 30.f, 30.f };
	m_fSpeed = 5.f;
	m_fDistance = 100.f;
}

int Player::Update()
{
	Key_Input();
	Obj::Update_Rect();

	return OBJ_NOEVENT;
}

void Player::Late_Update()
{
	Calc_Angle();
}

void Player::Render(HDC _hdc)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 153, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, myBrush);
	Rectangle(_hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(_hdc, oldBrush);
	DeleteObject(myBrush);

	MoveToEx(_hdc, (int)m_tInfo.fX, (int)m_tInfo.fY, nullptr);
	LineTo(_hdc, m_tPosin.x, m_tPosin.y);
}

void Player::Release()
{
}

void Player::Key_Input()
{
	if (GetAsyncKeyState('A'))
	{
		if (GetAsyncKeyState('W'))
		{
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
			if (GAME_WIN_LEFT >= (m_tInfo.fX - (m_tInfo.fCX * 0.5f))) {
				m_tInfo.fX += m_fSpeed / sqrtf(2.f);
				m_tInfo.fY += m_fSpeed / sqrtf(2.f);
			}
			if (GAME_WIN_TOP >= (m_tInfo.fY - (m_tInfo.fCY * 0.5f))) {
				m_tInfo.fX += m_fSpeed / sqrtf(2.f);
				m_tInfo.fY += m_fSpeed / sqrtf(2.f);
			}
		}
		else if (GetAsyncKeyState('S')) {
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
			if (GAME_WIN_LEFT >= (m_tInfo.fX - (m_tInfo.fCX * 0.5f))) {
				m_tInfo.fX += m_fSpeed / sqrtf(2.f);
				m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
			}
			if (GAME_WIN_BOTTOM <= (m_tInfo.fY + (m_tInfo.fCY * 0.5f))) {
				m_tInfo.fX += m_fSpeed / sqrtf(2.f);
				m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
			}
		}
		else {
			m_tInfo.fX -= m_fSpeed;
			if (GAME_WIN_LEFT >= (m_tInfo.fX - (m_tInfo.fCX * 0.5f))) {
				m_tInfo.fX += m_fSpeed;
			}
		}
	}
	else if (GetAsyncKeyState('D'))
	{
		if (GetAsyncKeyState('W'))
		{
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
			if (GAME_WIN_RIGHT <= (m_tInfo.fX + (m_tInfo.fCX * 0.5f))) {
				m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
				m_tInfo.fY += m_fSpeed / sqrtf(2.f);
			}
			if (GAME_WIN_TOP >= (m_tInfo.fY - (m_tInfo.fCY * 0.5f))) {
				m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
				m_tInfo.fY += m_fSpeed / sqrtf(2.f);
			}
		}
		else if (GetAsyncKeyState('S')) {
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
			if (GAME_WIN_RIGHT <= (m_tInfo.fX + (m_tInfo.fCX * 0.5f))) {
				m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
				m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
			}
			if (GAME_WIN_BOTTOM <= (m_tInfo.fY + (m_tInfo.fCY * 0.5f))) {
				m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
				m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
			}
		}
		else {
			m_tInfo.fX += m_fSpeed;
			if (GAME_WIN_RIGHT <= (m_tInfo.fX + (m_tInfo.fCX * 0.5f))) {
				m_tInfo.fX -= m_fSpeed;
			}
		}
	}
	else if (GetAsyncKeyState('W')) {
		m_tInfo.fY -= m_fSpeed;
		if (GAME_WIN_TOP >= (m_tInfo.fY - (m_tInfo.fCY * 0.5f))) {
			m_tInfo.fY += m_fSpeed;
		}
	}
	else if (GetAsyncKeyState('S')) {
		m_tInfo.fY += m_fSpeed;
		if (GAME_WIN_BOTTOM <= (m_tInfo.fY + (m_tInfo.fCY * 0.5f))) {
			m_tInfo.fY -= m_fSpeed;
		}
	}

	if (GetAsyncKeyState(WM_LBUTTONDOWN)) { //총알 여러개 방지
		if (!bKeyPressed) {
			m_BulletList->push_back(Create_Bullet(m_fAngle));
			bKeyPressed = true;
		}
		else {
			bKeyPressed = false;
		}
	}
}

void Player::Calc_Angle()
{
	POINT ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	float a = float(ptMouse.x) - m_tInfo.fX;
	float b = float(ptMouse.y) - m_tInfo.fY;
	float length = sqrtf(a * a + b * b);

	float angleCos = a / length;
	if (angleCos > 1.0f) angleCos = 1.0f;  
	if (angleCos < -1.0f) angleCos = -1.0f;  

	m_fAngle = acosf(angleCos) * (180.f / PI);

	if (b < 0) {
		m_fAngle = 360.0f - m_fAngle; 
	}

	m_tPosin.x = long(m_tInfo.fX + (m_fDistance * cosf(m_fAngle * (PI / 180.f))));
	m_tPosin.y = long(m_tInfo.fY + (m_fDistance * sinf(m_fAngle * (PI / 180.f))));
}

Obj* Player::Create_Bullet(float radian)
{
	return nullptr;
}
