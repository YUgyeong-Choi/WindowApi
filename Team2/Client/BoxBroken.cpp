#include "pch.h"
#include "BoxBroken.h"

BoxBroken::BoxBroken()
{
}

BoxBroken::~BoxBroken()
{
}

void BoxBroken::Initialize()
{
    // 상수는 수정해서 쓰면 될듯?
    m_tInfo = { WINCX - 450 , WINCY * 0.5f, 50.f, 50.f };
}

int BoxBroken::Update()
{
    if (m_bIsDead)
        return OBJ_DEAD;
    __super::UpdateRect();
    return OBJ_NOEVENT;
}

void BoxBroken::LateUpdate()
{
}

void BoxBroken::Render(HDC hDC)
{
    Rectangle(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
    if (g_bDevmode) Hitbox(hDC, m_tRect);
}

void BoxBroken::Release()
{
}

void BoxBroken::OnCollision(CObject* _op)
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
}
