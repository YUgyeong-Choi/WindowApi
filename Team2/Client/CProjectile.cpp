#include "pch.h"
#include "CProjectile.h"

void CProjectile::Initialize()
{
}

int CProjectile::Update()
{
	if (true == m_bIsDead)
		return OBJ_DEAD;
	return OBJ_NOEVENT;
}

void CProjectile::LateUpdate()
{
}

void CProjectile::Render(HDC hDC)
{
}

void CProjectile::Release()
{
}

void CProjectile::OnCollision(CObject* _op)
{
}

void CProjectile::OnDead()
{
}
