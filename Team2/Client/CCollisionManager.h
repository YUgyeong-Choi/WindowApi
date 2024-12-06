#pragma once
#include "CObject.h"
#include "Define.h"
class CCollisionManager
{
public:
	static void	CollisionRect(list<CObject*> _Dst, list<CObject*> _Src);

	static void	CollisionCircle(list<CObject*> _Dst, list<CObject*> _Src);
	static bool	CheckCircle(CObject* _Dst, CObject* _Src);

	static void	CollisionRectEx(list<CObject*> _Dst, list<CObject*> _Src);
	static bool	CheckRect(CObject* _Dst, CObject* _Src, float* pX, float* pY);

	static bool	CollisionLine(float _fX, float* pY);
};

