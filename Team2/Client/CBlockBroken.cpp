#include "pch.h"
#include "CBlockBroken.h"

CBlockBroken::CBlockBroken()
{
}

CBlockBroken::~CBlockBroken()
{
}

void CBlockBroken::Initialize()
{
    // 상수는 수정해서 쓰면 될듯?
    m_tInfo = { WINCX - 450 , WINCY * 0.5f, 50.f, 50.f };
    m_BlockType = BLOCK_BROKEN;
}

int CBlockBroken::Update()
{
    if (m_bIsDead)
        return OBJ_DEAD;
    __super::UpdateRect();
    return OBJ_NOEVENT;
}

void CBlockBroken::LateUpdate()
{
}

void CBlockBroken::Render(HDC hDC)
{
    // 나중에 텍스처 알아서 적용하기
    Rectangle(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
    if (g_bDevmode) Hitbox(hDC, m_tRect);
}

void CBlockBroken::Release()
{
}

void CBlockBroken::OnCollision(CObject* _op)
{
    if (OBJ_PLAYER == _op->GetOBJID())
    {
        if (m_tInfo.fY < _op->GetINFO().fY)
        {
            SetIsDead(true);

        }

    }
    if (OBJ_MONSTER == _op->GetOBJID())
    {

    }

    // 상, 하 충돌
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
        SetIsDead(true);
        _op->SetActionStatus(AS_FALL);
        _op->SetFallSpeed(50.f);
    }*/
}
