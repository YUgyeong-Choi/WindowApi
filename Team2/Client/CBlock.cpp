#include "pch.h"
#include "CBlock.h"
#include "CScrollManager.h"
#include "CItem.h"

void CBlock::Release()
{
}

CBlock::CBlock():m_RectType(RECT_END)
{
}

void CBlock::Initialize()
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
}

int CBlock::Update()
{
	if (m_bIsDead) {
		return OBJ_DEAD;
	}
	__super::UpdateRect();
	return 0;
}

void CBlock::LateUpdate()
{
}

void CBlock::Render(HDC hDC)
{ 
}


void CBlock::OnCollision(CObject* _op)
{


	//if (_op->GetOID() == OBJ_ITEM) {
	//	if (_op->GetINFO().fY < m_tInfo.fY) {
	//		_op->SetActionStatus(AS_STOP);
	//		_op->SetFallSpeed(3.f);
	//	}
	//}

	//if (m_RectType == RECT_ITEM) {
	//	if (_op->GetINFO().fY > m_tInfo.fY + m_tInfo.fCY*0.5f) {

	//	}
	//}

	//if (m_RectType == RECT_RANDOM) {
	//	if (_op->GetINFO().fY > m_tInfo.fY + m_tInfo.fCY * 0.5f) {
	//		CObjectManager::GetInstance()->Add_Object(OBJ_ITEM, CAbstractFactory<CItem>::Create());
	//		CObjectManager::GetInstance()->GetLastItem()->SetPos(m_tInfo.fX, m_tInfo.fY - 55.f);
	//		ChangeRectType(RECT_NONE);
	//	}
	//}


}

void CBlock::OnDead()
{
}