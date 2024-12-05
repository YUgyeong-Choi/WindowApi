#pragma once
#include "CObject.h"
#include "Define.h"

class CCollisionManager
{
public:
	static void	Collision_Rect(list<CObject*> _Dst, list<CObject*> _Src);

	static void	Collision_Circle(list<CObject*> _Dst, list<CObject*> _Src);
	//static bool	Check_Circle(CObject* _Dst, CObject* _Src);

	//static void	Collision_RectEx(list<CObject*> _Dst, list<CObject*> _Src);
	//static bool	Check_Rect(CObject* _Dst, CObject* _Src, float* pX, float* pY);
};

