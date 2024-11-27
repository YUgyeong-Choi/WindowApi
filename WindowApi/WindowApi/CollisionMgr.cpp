#include "CollisionMgr.h"

void CollisionMgr::Collision_RectRect(list<Obj*> _Dst, list<Obj*> _Src)
{
	RECT rc{};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, Dst->Get_Rect(), Src->Get_Rect()))
			{
				Dst->SetDead();
				Src->SetDead();
			}
		}
	}
}

void CollisionMgr::Collision_RectCircle(list<Obj*> _Dst, list<Obj*> _Src) 
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{ 
			float ax = Dst->Get_INFO().fX - Src->Get_INFO().fX; 
			float ay = Dst->Get_INFO().fY - Src->Get_INFO().fY; 
			float getVec = sqrt((ax * ax) + (ay * ay));
			if (getVec < (Dst->Get_INFO().fCX *0.5f) + Src->Get_INFO().fCX *0.5f) { 
				Dst->SetDead();
				Src->SetDead();
			}
		}
	}
}
