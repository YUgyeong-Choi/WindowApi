#include "pch.h"
#include "CMonsterYK2.h"
#include "CBitmapManager.h"
#include "CScrollManager.h"
#include "CObjectManager.h"
#include "CAbstractFactory.h"
#include "CMonsterBullet.h"

CMonsterYK2::CMonsterYK2():m_fDeadTime(0), m_iFireRate(0), m_iFireTick(0)
{
}

void CMonsterYK2::Initialize()
{
	m_tInfo = { 800, 400, 45, 70 };
	m_fSpeed = 3.f;
	m_tDir = { -1 , 1 };
	m_bIsGround = false;
    m_iFireRate = 30;
	CBitmapManager::GetInstance()->InsertBitmap(RESORUCEPATH L"Monster/Turtle/NormalTurtle/MonsterTurtleLeft.bmp", L"MonsterTurtleLeft");
	CBitmapManager::GetInstance()->InsertBitmap(RESORUCEPATH L"Monster/Turtle/NormalTurtle/MonsterTurtleRight.bmp", L"MonsterTurtleRight");
}

int CMonsterYK2::Update()
{
    if (m_bIsDead) return OBJ_DEAD;
    m_iFireTick++;

	if (FindPlayer()) {
		m_tInfo.fX += m_tDir.GetX() * m_fSpeed;
		m_tInfo.fY += m_tDir.GetY() * m_fSpeed;
		m_fTime += 0.2f;
		if (m_iFireRate < m_iFireTick) {
			Fire();
			m_iFireTick = 0;
		}
	}

	if (m_fTime >= 30) {
		m_tDir.SetX(m_tDir.GetX() * -1);
		m_fTime = 0.f;
	}

	if (m_fDeadTime > 0) {
		m_fDeadTime--;
		if (m_fDeadTime == 0) {
			SetIsDead(true);
		}
	}

	__super::UpdateRect();

    return 0;
}

void CMonsterYK2::LateUpdate()
{
	if (!m_bIsGround && m_fTime >= 2.f) m_tDir.SetY(1);
}

void CMonsterYK2::Render(HDC hDC)
{
	float	offset = CScrollManager::GetInstance()->GetScrollX();
	

	if (m_fDeadTime >= 0) {
		if (m_tDir.GetX() < 0) {
			HDC		hMemDC = CBitmapManager::GetInstance()->FindImage(L"MonsterTurtleLeft");
			GdiTransparentBlt(hDC,			// 복사 받을 DC
				m_tRect.left + (int)offset,	// 복사 받을 위치 좌표 X, Y	
				m_tRect.top,
				(int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
				(int)m_tInfo.fCY,
				hMemDC,						// 복사할 이미지 DC	
				0,							// 비트맵 출력 시작 좌표(Left, top)
				0,
				(int)45,			// 복사할 이미지의 가로, 세로
				(int)70,
				RGB(255, 255, 255));
		}
		else {
			HDC		hMemDC = CBitmapManager::GetInstance()->FindImage(L"MonsterTurtleRight");
			GdiTransparentBlt(hDC,			// 복사 받을 DC
				m_tRect.left + (int)offset,	// 복사 받을 위치 좌표 X, Y	
				m_tRect.top,
				(int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
				(int)m_tInfo.fCY,
				hMemDC,						// 복사할 이미지 DC	
				0,							// 비트맵 출력 시작 좌표(Left, top)
				0,
				(int)45,			// 복사할 이미지의 가로, 세로
				(int)70,
				RGB(255, 255, 255));
		}

	}
	else {
		HDC		hMemDC = CBitmapManager::GetInstance()->FindImage(L"MonsterTurtleLeft");
		GdiTransparentBlt(hDC,			// 복사 받을 DC
			m_tRect.left + (int)offset,	// 복사 받을 위치 좌표 X, Y	
			m_tRect.top,
			(int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
			(int)m_tInfo.fCY,
			hMemDC,						// 복사할 이미지 DC	
			45,							// 비트맵 출력 시작 좌표(Left, top)
			140,
			(int)45,			// 복사할 이미지의 가로, 세로
			(int)70,
			RGB(255, 255, 255));
	}


	if (g_bDevmode) Hitbox(hDC, m_tRect, { offset, 0 });
}

void CMonsterYK2::Release()
{
}

void CMonsterYK2::OnCollision(CObject* _op)
{
	if (_op->GetOBJID() == OBJ_PLAYER || _op->GetOBJID() == OBJ_PLAYER_BULLET) {
		m_fDeadTime = 5.f;
	}

	if (_op->GetOBJID() == OBJ_BLOCK) {
		m_tDir.SetX(m_tDir.GetX() * -1);
	}
}

void CMonsterYK2::OnDead()
{
}

void CMonsterYK2::Fire()
{
	CObjectManager::GetInstance()->Add_Object(OBJ_MONSTER_BULLET, CAbstractFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY));
}
