#include "pch.h"
#include "CMonsterBossYK.h"
#include "CScrollManager.h"
CMonsterBossYK::CMonsterBossYK():m_iDamageRate(0), m_PatternRate(0),m_iTick(0), m_isCanDamage(true), m_PatternTick(0), m_iPattern(0),m_iPatternCycle(0)
{
}
void CMonsterBossYK::Initialize()
{
	m_tInfo = { 3400, 400, 80, 80 };
	m_fSpeed = 3.f;
	m_tDir = { -1 , 1 };
	m_bIsGround = false;
	m_iHp = 100;
	m_iDamageRate = 13.f;
	m_PatternRate = 10000.f;
	m_fTime = 0.f;
}

int CMonsterBossYK::Update()
{
	if (m_bIsDead) return OBJ_DEAD;
	if (FindPlayer()) {
		m_PatternRate = 20.f;
		m_tInfo.fX += m_tDir.GetX() * m_fSpeed;
		m_tInfo.fY += m_tDir.GetY() * m_fSpeed;
	}
	m_iTick++;
	m_PatternTick++;
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
				m_iPatternCycle = 5;
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
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	//static BOOL Rectangle(HDC hDC, RECT tRect, Vector<float> offset = { 0, 0 })
	//{
	//	return Rectangle(hDC, tRect.left + offset.GetX(), tRect.top + offset.GetY(), tRect.right + offset.GetX(), tRect.bottom + offset.GetY());
	//}
	Rectangle(hDC, m_tInfo.fX-50 + CScrollManager::GetInstance()->GetScrollX(), m_tInfo.fY - 70, m_tInfo.fX+50+ CScrollManager::GetInstance()->GetScrollX(), m_tInfo.fY - 60);
	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);

	myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Rectangle(hDC, m_tInfo.fX - 50 + CScrollManager::GetInstance()->GetScrollX(), m_tInfo.fY - 70, m_tInfo.fX -50 + CScrollManager::GetInstance()->GetScrollX() + m_iHp , m_tInfo.fY - 60);
	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);

	
	Rectangle(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
	if (g_bDevmode) Hitbox(hDC, m_tRect);
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

void CMonsterBossYK::Pattern2() {
	m_PatternRate = 50.f;
	m_iPatternCycle--;
}
