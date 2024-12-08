#include "pch.h"
#include "CMonsterBullet.h"
#include "CScrollManager.h"

CMonsterBullet::CMonsterBullet()
{
}

void CMonsterBullet::Initialize()
{
    m_tInfo.fCX = 15.f;
    m_tInfo.fCY = 15.f;
    m_fSpeed = 4.f;
    m_fAngle = 0.f;
    m_ullTime = GetTickCount64();
}

int CMonsterBullet::Update()
{
    if (true == m_bIsDead)
        return OBJ_DEAD;

    if (m_ullTime + 3000 < GetTickCount64())
        return OBJ_DEAD;

    m_tInfo.fX += m_fSpeed * cosf(m_fAngle * PI / 180.f);
    m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * PI / 180.f);

    CObject::UpdateRect();

    return OBJ_NOEVENT;
}

void CMonsterBullet::LateUpdate()
{
}

void CMonsterBullet::Render(HDC hDC)
{
    Ellipse(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
}

void CMonsterBullet::Release()
{
}

void CMonsterBullet::OnCollision(CObject* _op)
{
}

void CMonsterBullet::Set_Degree()
{
    float fWitdh(0.f), fHeight(0.f), fDiagonal(0.f), fRadian(0.f);

    fWitdh = (m_tInfo.fX - m_pTarget->GetINFO().fX);
    fHeight = (m_tInfo.fY - m_pTarget->GetINFO().fY);

    fDiagonal = sqrtf(fWitdh * fWitdh + fHeight * fHeight);

    fRadian = acosf((m_pTarget->GetINFO().fX - m_tInfo.fX) / fDiagonal);

    m_fAngle = fRadian * (180.f / PI);

    if (m_pTarget->GetINFO().fY > m_tInfo.fY)
        m_fAngle = (PI / 180.f) - m_fAngle;
}
