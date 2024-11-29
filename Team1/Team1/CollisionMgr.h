#pragma once
#include "Obj.h"
class CollisionMgr
{
public:
	static void	Collision_Rect(list<Obj*> _Dst, list<Obj*> _Src);
	static void	Collision_Circle(list<Obj*> _Dst, list<Obj*> _Src);
private:
	int m_iRate;
};
