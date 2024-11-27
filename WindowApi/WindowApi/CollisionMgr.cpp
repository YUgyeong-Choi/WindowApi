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
}
