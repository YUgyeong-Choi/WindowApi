#include "pch.h"
#include "CRectangle.h"
#include "CScrollManager.h"
#include "CObjectManager.h"
#include "CAbstractFactory.h"
#include "CItem.h"

void CRectangle::Release()
{
}

CRectangle::CRectangle():m_RectType(RECT_END)
{
}

CRectangle::CRectangle(float _fX, float _fY, RECTANGLETYPE _type)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
	m_RectType = _type;
}

void CRectangle::Initialize()
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
}

int CRectangle::Update()
{
	if (m_bIsDead) {
		return OBJ_DEAD;
	}
	__super::UpdateRect();
	return 0;
}

void CRectangle::LateUpdate()
{
}

void CRectangle::Render(HDC hDC)
{

	if (m_RectType == RECT_ITEM) {
		HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(200, 103, 163));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
		Rectangle(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
		SelectObject(hDC, oldBrush);
		DeleteObject(myBrush);
	}
	else {
		Rectangle(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
	}

	
	if (g_bDevmode) Hitbox(hDC, m_tRect);
}


void CRectangle::OnCollision(CObject* _op)
{
	if (_op->GetOID() == OBJ_PLAYER || _op->GetOID() == OBJ_ITEM) {
		if (_op->GetINFO().fY < m_tInfo.fY) {
			_op->SetActionStatus(AS_STOP);
			_op->SetPos(_op->GetINFO().fX, (m_tInfo.fY - m_tInfo.fCY * 0.5f  - _op->GetINFO().fCY * 0.5f));
		}
	}



	if (m_RectType == RECT_ITEM) {
		if (_op->GetINFO().fY > m_tInfo.fY) {
			SetIsDead(true);
			_op->SetTIme();
			CObjectManager::GetInstance()->Add_Object(OBJ_ITEM, CAbstractFactory<CItem>::Create());
			CObjectManager::GetInstance()->GetLastItem()->SetPos(m_tInfo.fX, m_tInfo.fY);
		}
	}

}

void CRectangle::OnDead()
{
}