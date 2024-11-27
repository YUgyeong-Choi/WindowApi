#pragma once
#include "Obj.h"
#include "pch.h"

class CollisionMgr
{
public:
	static void	Collision_RectRect(list<Obj*> _Dst, list<Obj*> _Src);
	static void	Collision_RectCircle(list<Obj*> _Dst, list<Obj*> _Src);
};

