#pragma once
#include "../Client/CObject.h"
#include "../Client/Define.h"
class CCollisionManager
{
public:
	static void	CollisionRect(list<CObject*> _Dst, list<CObject*> _Src);

	static void	CollisionCircle(list<CObject*> _Dst, list<CObject*> _Src);
	static bool	CheckCircle(CObject* _Dst, CObject* _Src);

	static void	CollisionRectEx(list<CObject*> _Dst, list<CObject*> _Src);
	static void	CollisionRectEx2(list<CObject*> _Dst, list<CObject*> _Src);
	static void CollisionRectExDown(list<CObject*> _Dst, list<CObject*> _Src);
	static void CollisionTestRect(list<CObject*> _Dst, list<CObject*> _Src);
	static bool	CheckBox(CObject* _Dst, CObject* _Src, float* pX, float* pY);
	static bool	CheckBox2(CObject* _Dst, CObject* _Src, float* pX, float* pY);
	static bool	CheckBox3(CObject* _Dst, CObject* _Src, float* pX, float* pY);
	static bool	CheckBox4(CObject* _Dst, CObject* _Src, float* pX, float* pY);
	static bool	CheckRect(CObject* _Dst, CObject* _Src, float* pX, float* pY);


	static bool CheckRect(RECT& r1, RECT& r2);
	static bool	CheckRect(CObject* _Dst, CObject* _Src);

	static bool	CollisionLine(float _fX, float* pY);

	static void CollisionLine(CObject* player, list<CLine*> _l);

	static void	CollisionLine(list<CObject*> _Dst, list<CLine*> _Src);

	static CLine* CollisionLine2(float _fX, float* pY);
	static bool CheckLine(CObject* _Dst, CLine* _src);

	static bool	CollisionBox(float _fX, float* pY);

	static bool DetectPlayer(CObject* monster, CObject* player);
};