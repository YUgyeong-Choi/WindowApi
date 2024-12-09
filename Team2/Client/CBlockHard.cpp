#include "pch.h"
#include "CBlockHard.h"
#include "CBitmapManager.h"

CBlockHard::CBlockHard()
{
}

CBlockHard::~CBlockHard()
{
}

void CBlockHard::Initialize()
{
    m_tInfo = { m_tInfo.fX, m_tInfo.fY, 50.f, 50.f };
	m_BlockType = BLOCK_HARD;

	// 길게 선언해서 땅 이미지 하나만 불러와도 될듯?
	//m_tInfo.fCX = 2000.f;
	//m_tInfo.fCY = 50.f;
	CBitmapManager::GetInstance()->InsertBitmap(RESORUCEBLOCKPATH, L"Box");
}

int CBlockHard::Update()
{
	if (m_bIsDead == true)
	{
		return OBJ_DEAD;
	}

	__super::UpdateRect();
	return OBJ_NOEVENT;
}

void CBlockHard::LateUpdate()
{
}

void CBlockHard::Render(HDC hDC)
{
	float	offset = CScrollManager::GetInstance()->GetScrollX();
	HDC		hMemDC = CBitmapManager::GetInstance()->FindImage(L"Box");
	GdiTransparentBlt(hDC,			// 복사 받을 DC
		m_tRect.left + (int)offset,	// 복사 받을 위치 좌표 X, Y	
		m_tRect.top,
		(int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
		(int)m_tInfo.fCY,
		hMemDC,						// 복사할 이미지 DC	
		0,							// 비트맵 출력 시작 좌표(Left, top)
		0,
		(int)16,			// 복사할 이미지의 가로, 세로
		(int)16,
		RGB(255, 255, 255));
	if (g_bDevmode) Hitbox(hDC, m_tRect, { offset, 0 });
	//if (g_bDevmode) Hitbox(hDC, m_tRect);


}

void CBlockHard::Release()
{
}

void CBlockHard::OnCollision(CObject* _op)
{
	// 필요하면 쓰기

	// 상만 충돌
	/*if (_op->GetOBJID() == OBJ_PLAYER) {
		if (_op->GetINFO().fY < m_tInfo.fY) {
			_op->SetActionStatus(AS_STOP);
			_op->SetFallSpeed(3.f);
			_op->SetPos(_op->GetINFO().fX, (m_tInfo.fY - m_tInfo.fCY * 0.5f - _op->GetINFO().fCY * 0.5f));
		}
	}

	if (_op->GetOBJID() == OBJ_ITEM) {
		if (_op->GetINFO().fY < m_tInfo.fY) {
			_op->SetActionStatus(AS_STOP);
			_op->SetFallSpeed(3.f);
		}
	}

	if (_op->GetINFO().fY > m_tInfo.fY + m_tInfo.fCY * 0.5f) {
		_op->SetActionStatus(AS_FALL);
		_op->SetFallSpeed(50.f);
	}*/

	// 위, 좌, 우 충돌
	/*if (_op->GetOBJID() == OBJ_PLAYER) {
		if (_op->GetINFO().fY < m_tInfo.fY) {
			_op->SetActionStatus(AS_STOP);
			_op->SetFallSpeed(3.f);
			_op->SetPos(_op->GetINFO().fX, (m_tInfo.fY - m_tInfo.fCY * 0.5f - _op->GetINFO().fCY * 0.5f));
		}
	}

	if (_op->GetOBJID() == OBJ_ITEM) {
		if (_op->GetINFO().fY < m_tInfo.fY) {
			_op->SetActionStatus(AS_STOP);
			_op->SetFallSpeed(3.f);
		}
	}

	if (_op->GetOBJID() == OBJ_PLAYER) {
		if (m_tInfo.fY - m_tInfo.fCY * 0.5f < _op->GetINFO().fY) {
			if (m_tInfo.fX - m_tInfo.fCX * 0.5f <= _op->GetINFO().fX + _op->GetINFO().fCX * 0.5f && m_tInfo.fX > _op->GetINFO().fX) {
				_op->SetPos(m_tInfo.fX - m_tInfo.fCX * 0.5f - _op->GetINFO().fCX * 0.5f, _op->GetINFO().fY);
				_op->SetActionStatus(AS_FALL);
			}


			if (m_tInfo.fX + m_tInfo.fCX * 0.5f >= _op->GetINFO().fX - _op->GetINFO().fCX * 0.5f && m_tInfo.fX < _op->GetINFO().fX) {
				_op->SetPos(m_tInfo.fX + m_tInfo.fCX * 0.5f + _op->GetINFO().fCX * 0.5f, _op->GetINFO().fY);
				_op->SetActionStatus(AS_FALL);
			}
		}
	}*/

	//승훈
	//CBlock::OnCollision(_op);
	//if (_op->GetINFO().fY > m_tInfo.fY) // 플레이어 위치가 블럭 위치보다 낮다면
	//{
	//	_op->SetTime(3);               // 떨어지는 속도 증가
	//}
}
