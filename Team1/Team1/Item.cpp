#include "pch.h"
#include "Item.h"

Item::Item()
{
}

Item::~Item()
{
	Release();
}

void Item::Initialize()
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;
	m_fSpeed = 0.f;
	m_iHp = 1;
	m_iDamage = 0;
}

int Item::Update()
{
	if (m_bDead) {
		return OBJ_DEAD;
	}
	Obj::Update_Rect();
	return OBJ_NOEVENT;
}

void Item::Late_Update()
{
	if (m_iHp <= 0) {
		m_bDead = true;
		UseITem();
	}
}

void Item::Release()
{
}
