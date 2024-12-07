#include "pch.h"
#include "CNormalBlock.h"
#include "CScrollManager.h"

CNormalBlock::CNormalBlock()
{
}

void CNormalBlock::Initialize()
{
	m_tInfo.fCX = 2000.f;
	m_tInfo.fCY = 50.f;
}

void CNormalBlock::LateUpdate()
{
}

void CNormalBlock::Render(HDC hDC)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 220, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Rectangle(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);

}

void CNormalBlock::Release()
{
}

void CNormalBlock::OnCollision(CObject* _op)
{
	if (_op->GetOID() == OBJ_PLAYER ) {
		if (_op->GetINFO().fY < m_tInfo.fY) {
			_op->SetActionStatus(AS_STOP);
			_op->SetFallSpeed(3.f);
			_op->SetPos(_op->GetINFO().fX, (m_tInfo.fY - m_tInfo.fCY * 0.5f  - _op->GetINFO().fCY * 0.5f));
		}
	}	

	if (_op->GetOID() == OBJ_ITEM) {
		if (_op->GetINFO().fY < m_tInfo.fY) {
			_op->SetActionStatus(AS_STOP);
			_op->SetFallSpeed(3.f);
		}
	}

	if (_op->GetINFO().fY > m_tInfo.fY + m_tInfo.fCY * 0.5f) {
		_op->SetActionStatus(AS_FALL);
		_op->SetFallSpeed(50.f);
	}

}

void CNormalBlock::OnDead()
{
}
