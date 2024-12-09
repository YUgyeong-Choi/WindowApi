#include "pch.h"
#include "CMonsterYK1.h"
#include "CScrollManager.h"
#include "CBitmapManager.h"

CMonsterYK1::CMonsterYK1():m_fDeadTime(-1)
{
}

void CMonsterYK1::Initialize()
{
	m_tInfo = { 0, 0, 40, 40 };
	m_fSpeed = 3.f;
	m_tDir = { -1 , 1 };
	m_bIsGround = false;
	CBitmapManager::GetInstance()->InsertBitmap(RESORUCEPATH L"Monster/Mushroom/NormalMushroom/MonsterGoomBa.bmp", L"MonsterGoomBa");
}

int CMonsterYK1::Update()
{
	if (m_bIsDead) return OBJ_DEAD;
	if (FindPlayer()) {
		m_tInfo.fX += m_tDir.GetX() * m_fSpeed;
		m_tInfo.fY += m_tDir.GetY() * m_fSpeed;
		m_fTime += 0.2f;
	}

	if (m_fTime >= 30) {
		m_tDir.SetX(m_tDir.GetX()*-1);
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

void CMonsterYK1::LateUpdate()
{
	if (!m_bIsGround && m_fTime >= 2.f) m_tDir.SetY(1);
}

void CMonsterYK1::Render(HDC hDC)
{

	float	offset = CScrollManager::GetInstance()->GetScrollX();
	HDC		hMemDC = CBitmapManager::GetInstance()->FindImage(L"MonsterGoomBa");

	if (m_fDeadTime >= 0) {
		GdiTransparentBlt(hDC,			// 복사 받을 DC
			m_tRect.left + (int)offset,	// 복사 받을 위치 좌표 X, Y	
			m_tRect.top,
			(int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
			(int)m_tInfo.fCY,
			hMemDC,						// 복사할 이미지 DC	
			86,							// 비트맵 출력 시작 좌표(Left, top)
			0,
			(int)43,			// 복사할 이미지의 가로, 세로
			(int)40,
			RGB(0, 172, 255));
	}
	else {
		GdiTransparentBlt(hDC,			// 복사 받을 DC
			m_tRect.left + (int)offset,	// 복사 받을 위치 좌표 X, Y	
			m_tRect.top,
			(int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
			(int)m_tInfo.fCY,
			hMemDC,						// 복사할 이미지 DC	
			0,							// 비트맵 출력 시작 좌표(Left, top)
			0,
			(int)43,			// 복사할 이미지의 가로, 세로
			(int)40,
			RGB(0, 172, 255));
	}


	if (g_bDevmode) Hitbox(hDC, m_tRect, { offset, 0 });
}

void CMonsterYK1::Release()
{
}

void CMonsterYK1::OnCollision(CObject* _op)
{
	if (_op->GetOBJID() == OBJ_PLAYER || _op->GetOBJID() == OBJ_PLAYER_BULLET) {
		m_fDeadTime = 5.f;
	}


	if (_op->GetOBJID() == OBJ_BLOCK) {
		m_tDir.SetX(m_tDir.GetX() * -1);
	}
}

void CMonsterYK1::OnDead()
{
}
