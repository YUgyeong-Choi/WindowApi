#include "pch.h"
#include "BossHero.h"

BossHero::BossHero()
	:m_eState(STATE::IDLE), m_fCurSpeed(0.f), m_fChargeAngle(0.f)
	,ullLastStateChange_Time(0), m_pMonsterList(nullptr)
{
	ZeroMemory(&m_tChargePos, sizeof(POINT));
	
}

BossHero::~BossHero()
{
	Release();
}

void BossHero::ChargePattern()
{
}

void BossHero::Initialize()
{
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;
	m_fSpeed = 0.1f;

	m_iHp = 99;
	m_iDamage = 50;

	m_tInfo.fX = (GAME_WIN_RIGHT + GAME_WIN_LEFT) * 0.5f;
	m_tInfo.fY = GAME_WIN_TOP + m_tInfo.fCY;

	ullLastStateChange_Time = GetTickCount64();
	m_eState = IDLE;
}

int BossHero::Update()
{
	if (m_bDead) {
		return OBJ_DEAD;
	}

	//m_fSpeed += 0.015f; // 되면 set, getAccel 만들어서 바꾸기

	float   fWidth(0.f), fHeight(0.f), fDiagonal(0.f), fRadian(0.f);

	fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
	fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;

	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	fRadian = acosf(fWidth / fDiagonal);

	m_fAngle = fRadian * (180.f / PI);

	if (m_pTarget->Get_Info().fY > m_tInfo.fY)
		m_fAngle *= -1.f;
/////////////////////////////////////////////

	Obj::Update_Rect();

	return OBJ_NOEVENT;
}

void BossHero::Late_Update()
{
	if (m_iHp <= 0) {
		m_bDead = true;

		CreateThis();
	}

	//if (!m_bDead)
	//{
	//	if (m_ulTime + 500 < GetTickCount64())
	//	{
	//		Shoot();
	//		m_ulTime = GetTickCount64();
	//	}


	//}

	switch (m_eState)
	{
	case BossHero::IDLE:
		//몇초 뒤 READY_CHARGE

		if (ullLastStateChange_Time + 1000 < GetTickCount64())
		{
			m_eState = READY_CHARGE;
			ullLastStateChange_Time = GetTickCount64();
			m_tChargePos.x = Get_Info().fX;
			m_tChargePos.y = Get_Info().fY;
		}
		break;

	case BossHero::READY_CHARGE:

		//몇초 뒤
		if (ullLastStateChange_Time + 500 < GetTickCount64())
		{
			m_eState = CHARGE;
			ullLastStateChange_Time = GetTickCount64();
			m_fChargeAngle = m_fAngle;
		}

		//경로 그리기
		//m_tChargePos.x += 100.f * cos(m_fAngle * (PI / 180.f));
		//m_tChargePos.y -= 100.f * sin(m_fAngle * (PI / 180.f));

		m_tChargePos.x = m_pTarget->Get_Info().fX;
		m_tChargePos.y = m_pTarget->Get_Info().fY;

		//if (GAME_WIN_LEFT > m_tChargePos.x)
		//{
		//	m_tChargePos.x = GAME_WIN_LEFT;
		//}
		//if (GAME_WIN_RIGHT < m_tChargePos.x)
		//{
		//	m_tChargePos.x = GAME_WIN_RIGHT;
		//}
		//if (GAME_WIN_TOP > m_tChargePos.y)
		//{
		//	m_tChargePos.y = GAME_WIN_TOP;
		//}
		//if (GAME_WIN_BOTTOM < m_tChargePos.y)
		//{
		//	m_tChargePos.y = GAME_WIN_BOTTOM;
		//}

		break;

	case BossHero::CHARGE:

		//경로 그리기
		m_tChargePos.x += 10.f * cos(m_fChargeAngle * (PI / 180.f));
		m_tChargePos.y -= 10.f * sin(m_fChargeAngle * (PI / 180.f));

		/*if (GAME_WIN_LEFT > m_tChargePos.x)
		{
			m_tChargePos.x = GAME_WIN_LEFT;
		}
		if (GAME_WIN_RIGHT < m_tChargePos.x)
		{
			m_tChargePos.x = GAME_WIN_RIGHT;
		}
		if (GAME_WIN_TOP > m_tChargePos.y)
		{
			m_tChargePos.y = GAME_WIN_TOP;
		}
		if (GAME_WIN_BOTTOM < m_tChargePos.y)
		{
			m_tChargePos.y = GAME_WIN_BOTTOM;
		}*/

		//몇초 뒤
		if (ullLastStateChange_Time + 1000 > GetTickCount64())
		{
			break;
		}

		m_fCurSpeed += m_fSpeed;

		m_tInfo.fX += m_fCurSpeed * cosf(m_fChargeAngle * (PI / 180.f));
		m_tInfo.fY -= m_fCurSpeed * sinf(m_fChargeAngle * (PI / 180.f));

		//벽에 부딫히면 idle로
		if (IsOutMap())
		{
			m_eState = IDLE;
			ullLastStateChange_Time = GetTickCount64();
		}

		break;
	default:
		break;
	}
}

void BossHero::Render(HDC _hdc)
{
	if (m_eState == READY_CHARGE || m_eState == CHARGE)
	{
		HPEN hPen = CreatePen(PS_SOLID, Get_Info().fCX*0.1f, RGB(255, 0, 0));
		HPEN hOldPen = (HPEN)SelectObject(_hdc, hPen);
		// 경로 그리기
		MoveToEx(_hdc, Get_Info().fX, Get_Info().fY, NULL);
		LineTo(_hdc, m_tChargePos.x, m_tChargePos.y);
		// 원래 펜으로 복원
		SelectObject(_hdc, hOldPen);
		DeleteObject(hPen);
	}

	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(200, 103, 163));
	HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, myBrush);
	Rectangle(_hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(_hdc, oldBrush);
	DeleteObject(myBrush);
}

void BossHero::Set_Hp(int _iDamage)
{
	m_iHp += _iDamage;
}

bool BossHero::IsOutMap()
{
	bool bOutMap = false;

	//맵 밖을 나갈 수 없도록
	if (GAME_WIN_LEFT + m_tInfo.fCX * 0.5f > m_tInfo.fX)
	{
		m_tInfo.fX = GAME_WIN_LEFT + m_tInfo.fCX * 0.5f;
		bOutMap = true;
	}

	if (GAME_WIN_RIGHT - m_tInfo.fCX * 0.5f < m_tInfo.fX)
	{
		m_tInfo.fX = GAME_WIN_RIGHT - m_tInfo.fCX * 0.5f;
		bOutMap = true;
	}

	if (GAME_WIN_TOP + m_tInfo.fCY * 0.5f > m_tInfo.fY)
	{
		m_tInfo.fY = GAME_WIN_TOP + m_tInfo.fCY * 0.5f;
		bOutMap = true;
	}

	if (GAME_WIN_BOTTOM - m_tInfo.fCY * 0.5f < m_tInfo.fY)
	{
		m_tInfo.fY = GAME_WIN_BOTTOM - m_tInfo.fCY * 0.5f;
		bOutMap = true;
	}

	return bOutMap;
}

void BossHero::CreateThis()
{
	m_pMonsterList->push_back(new BossHero());
	m_pMonsterList->back()->Initialize();
	m_pMonsterList->back()->Set_Pos(Get_Info().fX - Get_Info().fCX, Get_Info().fY);
	static_cast<BossHero*>(m_pMonsterList->back())->IsOutMap();
	m_pMonsterList->back()->Set_Target(m_pTarget);
	static_cast<MonsterShoot*>(m_pMonsterList->back())->Set_Bullet(m_pBulletList);
	static_cast<BossHero*>(m_pMonsterList->back())->Set_MonsterList(m_pMonsterList);
	static_cast<BossHero*>(m_pMonsterList->back())->Set_Size(Get_Info().fCX * 0.8f, Get_Info().fCY * 0.8f);

	m_pMonsterList->push_back(new BossHero());
	m_pMonsterList->back()->Initialize();
	m_pMonsterList->back()->Set_Pos(Get_Info().fX + Get_Info().fCX, Get_Info().fY);
	static_cast<BossHero*>(m_pMonsterList->back())->IsOutMap();
	m_pMonsterList->back()->Set_Target(m_pTarget);
	static_cast<MonsterShoot*>(m_pMonsterList->back())->Set_Bullet(m_pBulletList);
	static_cast<BossHero*>(m_pMonsterList->back())->Set_MonsterList(m_pMonsterList);
	static_cast<BossHero*>(m_pMonsterList->back())->Set_Size(Get_Info().fCX * 0.8f, Get_Info().fCY * 0.8f);


}
