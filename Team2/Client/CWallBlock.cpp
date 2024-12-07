#include "pch.h"
#include "CWallBlock.h"
#include "CScrollManager.h"

CWallBlock::CWallBlock()
{
}

void CWallBlock::LateUpdate()
{
}

void CWallBlock::Render(HDC hDC)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 200));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Rectangle(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
}

void CWallBlock::Release()
{
}

void CWallBlock::OnCollision(CObject* _op)
{
	if (_op->GetOID() == OBJ_PLAYER) {
		if (_op->GetINFO().fY < m_tInfo.fY) {
			_op->SetActionStatus(AS_STOP);
			_op->SetFallSpeed(3.f);
			_op->SetPos(_op->GetINFO().fX, (m_tInfo.fY - m_tInfo.fCY * 0.5f - _op->GetINFO().fCY * 0.5f));
		}
	}

	if (_op->GetOID() == OBJ_ITEM) {
		if (_op->GetINFO().fY < m_tInfo.fY) {
			_op->SetActionStatus(AS_STOP);
			_op->SetFallSpeed(3.f);
		}
	}

	if (_op->GetOID() == OBJ_PLAYER) {
		if (m_tInfo.fY - m_tInfo.fCY * 0.5f < _op->GetINFO().fY) {
			if (m_tInfo.fX - m_tInfo.fCX * 0.5f <= _op->GetINFO().fX + _op->GetINFO().fCX * 0.5f && m_tInfo.fX > _op->GetINFO().fX) {
				_op->SetPos(m_tInfo.fX - m_tInfo.fCX * 0.5f - _op->GetINFO().fCX * 0.5f, _op->GetINFO().fY);
			}


			if (m_tInfo.fX + m_tInfo.fCX * 0.5f >= _op->GetINFO().fX - _op->GetINFO().fCX * 0.5f && m_tInfo.fX <_op->GetINFO().fX) {
				_op->SetPos(m_tInfo.fX + m_tInfo.fCX * 0.5f + _op->GetINFO().fCX * 0.5f, _op->GetINFO().fY);
			}
		}
	}
}

void CWallBlock::OnDead()
{
}
