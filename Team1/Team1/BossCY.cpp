#include "pch.h"
#include "BossCY.h"
#include "Define.h"
#include "BulletOne.h"

void BossCY::Initialize()
{
	m_tInfo.fCX = 70.f;
	m_tInfo.fCY = 70.f;
	m_fSpeed = 1.5f;

	m_iHp = 5000;
	m_iDamage = 1;

	m_tInfo.fY = 1;
	m_tInfo.fX = GAME_WINCX / 2;
	m_ullMovingInterval = 1000;
	m_bMovingPattern[BOSSMOVESTART] = true;
	m_iRotateNum = 0;
}

void BossCY::Set_Hp(int _iDamage)
{
	m_iHp += _iDamage;
}

void BossCY::MoveBoss(BOSSMOVE _Type)
{
	switch (_Type)
	{
	case BossCY::BOSSMOVESTART:
		if (m_tInfo.fY < 100.f)
		{
			if (m_tInfo.fX > GAME_WINCX / 2)
				m_tInfo.fX += m_fSpeed;
			m_tInfo.fY += m_fSpeed;
			m_ullMovingTick = GetTickCount64();
		}
		else if (m_tInfo.fY >= 100.f) {
			m_fSpeed = 0;
			if (m_ullMovingTick + m_ullMovingInterval <= GetTickCount64())
			{
				m_bMovingPattern[BOSSMOVESTART] = false;
				m_bMovingPattern[ROTATEPAT1] = true;
				m_fSpeed = 3.f;
				m_ullMovingTick = GetTickCount64();
			}
		}
		break;
	case BossCY::ROTATEPAT1:
		if (m_tInfo.fX > 100.f)
		{
			m_tInfo.fX -= m_fSpeed;
			m_ullMovingTick = GetTickCount64();
		}
		else if (m_tInfo.fX <= 100.f) {
			m_fSpeed = 0;
			if (m_ullMovingTick + m_ullMovingInterval <= GetTickCount64())
			{
				m_bMovingPattern[ROTATEPAT1] = false;
				m_bMovingPattern[ROTATEPAT2] = true;
				m_fSpeed = 3.f;
				m_ullMovingTick = GetTickCount64();
			}
		}
		break;
	case BossCY::ROTATEPAT2:
		if (m_tInfo.fY < GAME_WINCY - 100.f)
		{
			m_tInfo.fY += m_fSpeed;
			m_ullMovingTick = GetTickCount64();
		}
		else if (m_tInfo.fY >= GAME_WINCY - 100.f) {
			m_fSpeed = 0;
			if (m_ullMovingTick + m_ullMovingInterval <= GetTickCount64())
			{
				m_bMovingPattern[ROTATEPAT2] = false;
				m_bMovingPattern[ROTATEPAT3] = true;
				m_fSpeed = 3.f;
				m_ullMovingTick = GetTickCount64();
			}
		}
		break;
	case BossCY::ROTATEPAT3:
		if (m_tInfo.fX < GAME_WINCX - 100.f)
		{
			m_tInfo.fX += m_fSpeed;
			m_ullMovingTick = GetTickCount64();
		}
		else if (m_tInfo.fX >= GAME_WINCX - 100.f) {
			m_fSpeed = 0;
			if (m_ullMovingTick + m_ullMovingInterval <= GetTickCount64())
			{
				m_bMovingPattern[ROTATEPAT3] = false;
				m_bMovingPattern[ROTATEPAT4] = true;
				m_fSpeed = 3.f;
				m_ullMovingTick = GetTickCount64();
			}
		}
		break;
	case BossCY::ROTATEPAT4:
		if (m_tInfo.fY > 100.f)
		{
			m_tInfo.fY -= m_fSpeed;
			m_ullMovingTick = GetTickCount64();
		}
		else if (m_tInfo.fY <= 100.f) {
			m_fSpeed = 0;
			++m_iRotateNum;
			if (m_ullMovingTick + m_ullMovingInterval <= GetTickCount64())
			{
				m_bMovingPattern[ROTATEPAT4] = false;
				if (m_iRotateNum < 2)
				{
					m_bMovingPattern[ROTATEPAT1] = true;
					m_fSpeed = 3.f;
				}
				else
				{
					m_bMovingPattern[FOLLOWPAT] = true;
					m_fSpeed = 2.f;
				}
				m_ullMovingTick = GetTickCount64();
			}
		}
		break;
	case BossCY::FOLLOWPAT:
		FollowPlayer();
		break;
	case BossCY::CENTERPAT:
		MoveToCenter();
		break;
	case BossCY::RETURNPAT:
		if (m_tInfo.fY > 100.f)
		{
			m_tInfo.fY -= m_fSpeed;
			m_ullMovingTick = GetTickCount64();
		}
		else if (m_tInfo.fY <= 100.f) {
			m_fSpeed = 0;
			if (m_ullMovingTick + m_ullMovingInterval <= GetTickCount64())
			{
				m_bMovingPattern[RETURNPAT] = false;
				m_bMovingPattern[ROTATEPAT1] = true;
				m_iRotateNum = 0;
				m_fSpeed = 3.f;
				m_ullMovingTick = GetTickCount64();
			}
		}
	default:
		break;
	}
}

void BossCY::BulletPattern(BOSSMOVE _Type)
{
	switch (_Type)
	{
	case BossCY::ROTATEPAT1:
	case BossCY::ROTATEPAT2:
	case BossCY::ROTATEPAT3:
	case BossCY::ROTATEPAT4:
		if (m_ulTime + 500 < GetTickCount64())
		{
			for (int i = 0; i < 18; ++i)
			{
				m_pBulletList->push_back(new BulletOne);
				m_pBulletList->back()->Initialize();
				m_pBulletList->back()->Set_Angle(m_fAngle * (PI / 180.f) + i * 20);
				m_pBulletList->back()->Set_Pos(m_tInfo.fX, m_tInfo.fY);
				dynamic_cast<Bullet*>(m_pBulletList->back())->Set_Type(BM_MONSTER);
			}
			m_ulTime = GetTickCount64();
		}
		break;
	case BossCY::FOLLOWPAT:
		break;
	case BossCY::CENTERPAT:
		if (m_ulTime < GetTickCount64())
		{
			m_pBulletList->push_back(new BulletOne);
			m_pBulletList->back()->Initialize();
			m_pBulletList->back()->Set_Angle(m_fAngle * (PI / 180.f) + m_iTemp * 15);
			m_pBulletList->back()->Set_Pos(m_tInfo.fX, m_tInfo.fY);
			dynamic_cast<Bullet*>(m_pBulletList->back())->Set_Type(BM_MONSTER);
			m_ulTime = GetTickCount64();
		}
		m_iTemp++;
		break;
	case BossCY::RETURNPAT:
		break;
	default:
		break;
	}
}

void BossCY::FollowPlayer()
{
	m_fSpeed = 2.f;
	m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
	if (m_tInfo.fX + 35.f >= GAME_WINCX)
		m_tInfo.fX = GAME_WINCX - 35.f;
	else if (m_tInfo.fX <= 35.f)
		m_tInfo.fX = 35.f;
	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));
	if (m_tInfo.fY + 35.f >= GAME_WINCY)
		m_tInfo.fY = GAME_WINCY - 35.f;
	else if (m_tInfo.fY <= 35.f)
		m_tInfo.fY = 35.f;
	if (m_ullMovingTick + 5000 <= GetTickCount64())
	{
		m_bMovingPattern[FOLLOWPAT] = false;
		m_bMovingPattern[CENTERPAT] = true;
		m_fSpeed = 3.f;
		m_ullMovingTick = GetTickCount64();
	}
}

void BossCY::MoveToCenter()
{
	float   fWidth(0.f), fHeight(0.f), fDiagonal(0.f), fRadian(0.f);

	fWidth = GAME_WINCX * 0.5f - m_tInfo.fX;
	fHeight = GAME_WINCY * 0.5f - m_tInfo.fY;

	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	fRadian = acosf(fWidth / fDiagonal);

	m_fCenterAngle = fRadian * (180.f / PI);

	if (GAME_WINCY * 0.5f > m_tInfo.fY)
		m_fCenterAngle *= -1.f;

	

	if (m_tInfo.fX <= GAME_WINCX * 0.5f + 5.f && m_tInfo.fX >= GAME_WINCX * 0.5f - 5.f)
	{
		if (m_tInfo.fY <= GAME_WINCY * 0.5f + 5.f && m_tInfo.fY >= GAME_WINCY * 0.5f - 5.f)
			m_fSpeed = 0;
	}

	m_tInfo.fX += m_fSpeed * cosf(m_fCenterAngle * (PI / 180.f));
	m_tInfo.fY -= m_fSpeed * sinf(m_fCenterAngle * (PI / 180.f));


	if (m_ullMovingTick + 3000 <= GetTickCount64())
	{
		m_bMovingPattern[CENTERPAT] = false;
		m_bMovingPattern[RETURNPAT] = true;
		m_fSpeed = 3.0f;
		m_ullMovingTick = GetTickCount64();
	}
}

int BossCY::Update()
{
	if (m_bDead) {
		return OBJ_DEAD;
	}

	float   fWidth(0.f), fHeight(0.f), fDiagonal(0.f), fRadian(0.f);

	fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
	fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;

	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	fRadian = acosf(fWidth / fDiagonal);

	m_fAngle = fRadian * (180.f / PI);

	if (m_pTarget->Get_Info().fY > m_tInfo.fY)
		m_fAngle *= -1.f;

	for (int i = 0; i < BOSSMOVEEND; ++i)
	{
		if (m_bMovingPattern[i])
		{
			MoveBoss((BOSSMOVE)i);
		}
	}

	Obj::Update_Rect();

	return OBJ_NOEVENT;
}

void BossCY::Late_Update()
{
	if (m_iHp <= 0) {
		m_bDead = true;
	}
	if (!m_bDead)
	{
		for (int i = 0; i < BOSSMOVEEND; ++i)
		{
			if (m_bMovingPattern[i])
			{
				BulletPattern((BOSSMOVE)i);
			}
		}
		
		for (int i = 0; i < BOSSMOVEEND; ++i)
		{
			if (m_bMovingPattern[i])
			{
				MoveBoss((BOSSMOVE)i);
			}
		}
	}
}

void BossCY::Render(HDC _hdc)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(130, 10, 20));
	HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, myBrush);
	Rectangle(_hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(_hdc, oldBrush);
	DeleteObject(myBrush);
}