#include "pch.h"
#include "Player.h"
#include "BulletOne.h"
#include "BulletScrew.h"

Player::Player() :  m_tPosin({}), m_BulletList(nullptr), m_iBulletLevel(BULLET_ONE), m_iFireRate(0), m_iTick(0), m_pShieldList(nullptr)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	m_tInfo = { WINCX / 2.f, WINCY / 2.f, 30.f, 30.f };
	m_fSpeed = 5.f;
	m_fDistance = 30.f;
	m_iBulletLevel = BULLET_SCREW;
	m_iFireRate = 13;
	m_iTick = 0;

	m_iHp = 100;
	m_iDamage = 10;
}

int Player::Update()
{
	if (m_bDead) {
		return OBJ_DEAD;
	}
	++m_iTick;
	Key_Input();
	Obj::Update_Rect();

	return OBJ_NOEVENT;
}

void Player::Late_Update()
{
	Calc_Angle();
	if (m_iHp <= 0) {
		m_bDead = true;
	}
}

void Player::Render(HDC _hdc)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
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

void Player::Upgrade_Bullet()
{
	++m_iBulletLevel;
	if (m_iBulletLevel > BULLET_SCREW) {
		--m_iBulletLevel;
	}
}

void Player::Set_SSpeed(int _iRate)
{
	m_fSpeed -= _iRate;
	if (m_fSpeed < 0) {
		m_fSpeed += _iRate;
	}
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

	if (GetAsyncKeyState(VK_LBUTTON)) { //총알 여러개 방지
		if (m_iTick >= m_iFireRate) {
			Obj* pBullet(nullptr);
			switch (m_iBulletLevel)
			{
			case BULLET_ONE:
				pBullet = new BulletOne(m_fAngle);
				pBullet->Initialize();
				pBullet->Set_Pos(float(m_tPosin.x), float(m_tPosin.y));
				m_BulletList->push_back(pBullet);
				break;
			case BULLET_TWO:
				pBullet = new BulletOne(m_fAngle - 5.f);
				pBullet->Initialize();
				pBullet->Set_Pos(float(m_tPosin.x), float(m_tPosin.y));
				m_BulletList->push_back(pBullet);


				pBullet = new BulletOne(m_fAngle +5.f);
				pBullet->Initialize();
				pBullet->Set_Pos(float(m_tPosin.x), float(m_tPosin.y));
				m_BulletList->push_back(pBullet);
				break;
			case BULLET_THREE:
				pBullet = new BulletOne(m_fAngle-10.f);
				pBullet->Initialize();
				pBullet->Set_Pos(float(m_tPosin.x), float(m_tPosin.y));
				m_BulletList->push_back(pBullet);

				pBullet = new BulletOne(m_fAngle);
				pBullet->Initialize();
				pBullet->Set_Pos(float(m_tPosin.x), float(m_tPosin.y));
				m_BulletList->push_back(pBullet);


				pBullet = new BulletOne(m_fAngle+10.f);
				pBullet->Initialize();
				pBullet->Set_Pos(float(m_tPosin.x), float(m_tPosin.y));
				m_BulletList->push_back(pBullet);
				break;
			case BULLET_SCREW:
				pBullet = new BulletScrew(m_fAngle);
				pBullet->Initialize();
				pBullet->Set_Pos(float(m_tPosin.x), float(m_tPosin.y));
				m_BulletList->push_back(pBullet);
				break;
			default:
				break;
			}
			m_iTick = 0;
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

	m_fAngle = acosf(angleCos) * (180.f / PI);

	if (b > 0) {
		m_fAngle = 360.0f - m_fAngle; 
	}

	m_tPosin.x = long(m_tInfo.fX + (m_fDistance * cosf(m_fAngle * (PI / 180.f))));
	m_tPosin.y = long(m_tInfo.fY - (m_fDistance * sinf(m_fAngle * (PI / 180.f))));
}
