#include "pch.h"
#include "CollisionMgr.h"

void CollisionMgr::Collision_Rect(list<Obj*> _Dst, list<Obj*> _Src)
{
	RECT rc{};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, Dst->Get_Rect(), Src->Get_Rect()))
			{
				Dst->Set_Hp(-Src->Get_Damage());
				Src->Set_Hp(-Dst->Get_Damage());
			}
		}
	}
}

void CollisionMgr::Collision_Circle(list<Obj*> _Dst, list<Obj*> _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			float ax = Dst->Get_Info().fX - Src->Get_Info().fX;
			float ay = Dst->Get_Info().fY - Src->Get_Info().fY;
			float getVec = sqrtf((ax * ax) + (ay * ay));
			if (getVec < (Dst->Get_Info().fCX * 0.5f) + Src->Get_Info().fCX * 0.5f) {
				Dst->Set_Hp(-Src->Get_Damage());
				Src->Set_Hp(-Dst->Get_Damage());
			}
		}
	}
}
