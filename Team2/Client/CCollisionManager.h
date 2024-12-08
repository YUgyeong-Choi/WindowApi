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
	 
	// 추가 하면 아래 적어주고 설명도 같이좀
	static bool CheckRect(RECT& r1, RECT& r2);
	static bool	CheckRect(CObject* _Dst, CObject* _Src);

	static bool CollisionLine(INFO _tInfo, float* pY);
};

