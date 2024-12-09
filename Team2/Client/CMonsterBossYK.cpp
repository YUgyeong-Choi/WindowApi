#include "pch.h"
#include "CMonsterBossYK.h"
#include "CScrollManager.h"
#include "CObjectManager.h"
#include "CAbstractFactory.h"
#include "CMonsterBullet.h"
CMonsterBossYK::CMonsterBossYK():m_iDamageRate(0), m_PatternRate(0),m_iTick(0), m_isCanDamage(true), m_PatternTick(0), m_iPattern(0),m_iPatternCycle(0), m_iFireRate(0),m_iFireTick(0)
{
}
void CMonsterBossYK::Initialize()
{
	m_tInfo = { 2800, 400, 80, 80 };
	m_fSpeed = 3.f;
	m_tDir = { -1 , 1 };
	m_bIsGround = false;
	m_iHp = 100;
	m_iDamageRate = 13.f;
	m_PatternRate = 10000.f;
	m_fTime = 0.f;
	m_iFireRate = 20.f;
}

int CMonsterBossYK::Update()
{
	if (m_bIsDead) return OBJ_DEAD;
	if (FindPlayer()) {
		switch (m_iPattern)
		{
		case 0:
			m_PatternRate = 25.f;
			break;
		case 1:
			m_PatternRate = 20.f;
			break;
		default:
			break;
		}
		
		m_tInfo.fX += m_tDir.GetX() * m_fSpeed;
		m_tInfo.fY += m_tDir.GetY() * m_fSpeed;
	}
	m_iTick++;
	m_PatternTick++;
	m_iFireTick++;
	if (m_iTick > m_iDamageRate) {
		if (!m_isCanDamage) { 
 			m_isCanDamage = true;
		}
		m_iTick = 0;
	}

	if (m_PatternTick > m_PatternRate) {
		switch (m_iPattern)
		{
		case 0:
			if (m_iPatternCycle == 0) {
				m_iPatternCycle = 3;
			}
			Pattern1();
			break;
		case 1:
			if (m_iPatternCycle == 0) {
				m_iPatternCycle = 15;
			}
			Pattern2();
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
		}

		if (m_iPatternCycle == 0) {
			m_iPattern++;
			if (m_iPattern == 4) {
				m_iPattern = 0;
			}
		}
		m_PatternTick = 0;
	}

	__super::UpdateRect();
	return 0;
}
 
void CMonsterBossYK::LateUpdate()
{
	if (m_iHp <= 0) {
		SetIsDead(true);
	}
}

void CMonsterBossYK::Render(HDC hDC)
{
	float	offset = CScrollManager::GetInstance()->GetScrollX();
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Rectangle(hDC, m_tInfo.fX-50 + CScrollManager::GetInstance()->GetScrollX(), m_tInfo.fY - 70, m_tInfo.fX+50+ CScrollManager::GetInstance()->GetScrollX(), m_tInfo.fY - 60);
	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);

	myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Rectangle(hDC, m_tInfo.fX - 50 + CScrollManager::GetInstance()->GetScrollX(), m_tInfo.fY - 70, m_tInfo.fX -50 + CScrollManager::GetInstance()->GetScrollX() + m_iHp , m_tInfo.fY - 60);
	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);

	
	Rectangle(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
	if (g_bDevmode) Hitbox(hDC, m_tRect, { offset, 0 });
}

void CMonsterBossYK::Release()
{
}

void CMonsterBossYK::OnCollision(CObject* _op)
{
	if (_op->GetOBJID() == OBJ_PLAYER) {
		if (m_isCanDamage) {
			m_iHp -= 5;
			m_isCanDamage = false;
		}
	}

	if (_op->GetOBJID() == OBJ_PLAYER_BULLET) {
		m_iHp -= 3;
	}

	if (_op->GetOBJID() == OBJ_BLOCK) {
		m_tDir.SetX(m_tDir.GetX() * -1);
	}
}

void CMonsterBossYK::OnDead()
{
}

void CMonsterBossYK::Pattern1()
{
	m_PatternRate = 20.f;
	m_bIsGround = false;
	m_tDir.SetY(-1);
	m_fTime += 1.f;
	if (m_fTime >= 2) {
		m_iPatternCycle--;
		m_fTime = 0.f;
		m_tDir.SetY(1);
	}
}

void CMonsterBossYK::Pattern2() 
{
	if (m_iFireTick > m_iFireRate) {
		if (rand() % 2 == 0) {
			CObjectManager::GetInstance()->Add_Object(OBJ_MONSTER_BULLET, CAbstractFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY - 40));
			CObjectManager::GetInstance()->Add_Object(OBJ_MONSTER_BULLET, CAbstractFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY - 20));

		}
		else {
			CObjectManager::GetInstance()->Add_Object(OBJ_MONSTER_BULLET, CAbstractFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY +40));
			CObjectManager::GetInstance()->Add_Object(OBJ_MONSTER_BULLET, CAbstractFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY +20));
		}

		m_iFireTick = 0;
	}
	m_iPatternCycle--;
}
