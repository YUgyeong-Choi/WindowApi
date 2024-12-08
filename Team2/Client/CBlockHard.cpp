#include "pch.h"
#include "CBlockHard.h"

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

	// ��� �����ؼ� �� �̹��� �ϳ��� �ҷ��͵� �ɵ�?
	//m_tInfo.fCX = 2000.f;
	//m_tInfo.fCY = 50.f;
    
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
	// ���߿� �ؽ�ó �˾Ƽ� �����ϱ�
	Rectangle(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
	if (g_bDevmode) Hitbox(hDC, m_tRect);
}

void CBlockHard::Release()
{
}

void CBlockHard::OnCollision(CObject* _op)
{
	// �ʿ��ϸ� ����

	// �� �浹
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

	// ��, ��, �� �浹
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

	//����
	//CBlock::OnCollision(_op);
	//if (_op->GetINFO().fY > m_tInfo.fY) // �÷��̾� ��ġ�� �� ��ġ���� ���ٸ�
	//{
	//	_op->SetTime(3);               // �������� �ӵ� ����
	//}
}
