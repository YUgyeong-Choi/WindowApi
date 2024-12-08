#include "pch.h"
#include "CFollowMonster.h"
#include "CObjectManager.h"
#include "CAbstractFactory.h"
#include "CMonsterBullet.h"
#include "CScrollManager.h"
#include "CCollisionManager.h"

CFollowMonster::CFollowMonster()
{
}

void CFollowMonster::Initialize()
{
    m_tInfo.fCX = 35.f;
    m_tInfo.fCY = 35.f;
    m_fSpeed = 2.f;
    m_ullTime = GetTickCount64();
    m_eAction = AS_STOP;
}

int CFollowMonster::Update()
{
    if (true == m_bIsDead)
        return OBJ_DEAD;

    float fY(0.f);

    bool bLineCol = CCollisionManager::CollisionLine(m_tInfo, &fY);


    if (true == FindPlayer())
        SetActionStatus(AS_MOVE_LEFT);
    else
        SetActionStatus(AS_STOP);

    if (bLineCol && AS_STOP != GetActionStatus())
    {
        m_tInfo.fY = fY - m_tInfo.fCY * 0.5f;
        if (m_tInfo.fX <= m_pTarget->GetINFO().fX - 100)
            m_tInfo.fX += m_fSpeed;
        else if (m_tInfo.fX >= m_pTarget->GetINFO().fX + 100)
            m_tInfo.fX -= m_fSpeed;
    }

    CObject::UpdateRect();

    return OBJ_NOEVENT;
}

void CFollowMonster::LateUpdate()
{
    if (m_ullTime + 5000 < GetTickCount64() && AS_STOP != GetActionStatus()) // 5초에 한 번 씩
    {
        CObjectManager::GetInstance()->Add_Object(OBJ_MONSTER_BULLET, CAbstractFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY)); // 플레이어 추적하는 총알 발사
        CObjectManager::GetInstance()->GetLastMonsterBullet()->SetTargetObject(m_pTarget);
        dynamic_cast<CMonsterBullet*>(CObjectManager::GetInstance()->GetLastMonsterBullet())->Set_Degree(); // 최초 1회 타깃 설정
        m_ullTime = GetTickCount64();
    }
}

void CFollowMonster::Render(HDC hDC)
{
    Rectangle(hDC, m_tRect, { CScrollManager::GetInstance()->GetScrollX(), 0 });
}

void CFollowMonster::Release()
{
}

void CFollowMonster::OnCollision(CObject* _op)
{
}
