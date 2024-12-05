#include "pch.h"
#include "CCollisionManager.h"
void CCollisionManager::Collision_Rect(list<CObject*> _Dst, list<CObject*> _Src)
{
	RECT rc{};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			//if (IntersectRect(&rc, Dst->Get_Rect(), Src->Get_Rect()))
			//{
			//	Dst->Set_Dead();
			//	Src->Set_Dead();
			//}
		}
	}

}

void CCollisionManager::Collision_Circle(list<CObject*> _Dst, list<CObject*> _Src)
{
	RECT rc{};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			//if (Check_Circle(Dst, Src))
			//{
			//	Dst->Set_Dead();
			//	Src->Set_Dead();
			//}
		}
	}
}

//bool CCollisionManager::Check_Circle(CObject* _Dst, CObject* _Src)
//{
//	float fRadius = (_Dst->Get_Info().fCX + _Src->Get_Info().fCX) * 0.5f;
//
//	float fWidth = abs(_Dst->Get_Info().fX - _Src->Get_Info().fX);
//	float fHeight = abs(_Dst->Get_Info().fY - _Src->Get_Info().fY);
//
//	float fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);
//
//	return fRadius >= fDiagonal;
//}
