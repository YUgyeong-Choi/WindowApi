#include "pch.h"
#include "CSecretBlock.h"
#include "CScrollManager.h"
#include "CObjectManager.h"
#include "CAbstractFactory.h"
#include "CItem.h"

CSecretBlock::CSecretBlock():m_bActive(true)
{
}

void CSecretBlock::LateUpdate()
{
}

void CSecretBlock::Render(HDC hDC)
{
	if (m_bActive) {
		HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 220, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
		Rectangle(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
		SelectObject(hDC, oldBrush);
		DeleteObject(myBrush);
	}
	else {
		HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(100, 220, 100));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
		Rectangle(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
		SelectObject(hDC, oldBrush);
		DeleteObject(myBrush);
	}

}

void CSecretBlock::Release()
{
}

void CSecretBlock::OnCollision(CObject* _op)
{
	if (_op->GetOID() == OBJ_PLAYER ) {
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

	if (_op->GetINFO().fY > m_tInfo.fY + m_tInfo.fCY * 0.5f) {
		_op->SetActionStatus(AS_FALL);
		_op->SetFallSpeed(50.f);
		if (m_bActive) {
			CObjectManager::GetInstance()->Add_Object(OBJ_ITEM, CAbstractFactory<CItem>::Create());
			CObjectManager::GetInstance()->GetLastItem()->SetPos(m_tInfo.fX, m_tInfo.fY - 60.f);
			m_bActive = false;
		}
	}
}

void CSecretBlock::OnDead()
{
}
