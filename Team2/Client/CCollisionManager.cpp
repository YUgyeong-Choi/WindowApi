#include "pch.h"
#include "CCollisionManager.h"
#include "CLineManager.h"
#include "CObjectManager.h"

void CCollisionManager::CollisionRect(list<CObject*> _Dst, list<CObject*> _Src)
{
	RECT rc{};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, Dst->GetRECT(), Src->GetRECT()))
			{
				Dst->OnCollision(Src);
				Src->OnCollision(Dst);
			}
		}
	}
}

void CCollisionManager::CollisionCircle(list<CObject*> _Dst, list<CObject*> _Src)
{
	RECT rc{};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (CheckCircle(Dst, Src))
			{
				Dst->OnCollision(Src);
				Src->OnCollision(Dst);
			}
		}
	}
}

bool CCollisionManager::CheckCircle(CObject* _Dst, CObject* _Src)
{
	float fRadius = (_Dst->GetINFO().fCX + _Src->GetINFO().fCX) * 0.5f;

	float fWidth = abs(_Dst->GetINFO().fX - _Src->GetINFO().fX);
	float fHeight = abs(_Dst->GetINFO().fY - _Src->GetINFO().fY);

	float fDiagonal = powf((fWidth * fWidth + fHeight * fHeight), 0.5f);

	return fRadius >= fDiagonal;
}

void CCollisionManager::CollisionRectEx(list<CObject*> _Dst, list<CObject*> _Src)
{
	float	fX(0.f), fY(0.f);

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (CheckRect(Dst, Src, &fX, &fY))
			{
				// 상 하 충돌
				if (fX > fY)
				{
					// 상 충돌
					if (Dst->GetINFO().fY < Src->GetINFO().fY)
					{
						Dst->SetPos(Dst->GetINFO().fX, -fY);
					}
					// 하 충돌
					else
					{
						Dst->SetPos(Dst->GetINFO().fX, fY);
					}
				}

				// 좌 우 충돌
				else
				{
					// 좌 충돌
					if (Dst->GetINFO().fX < Src->GetINFO().fX)
					{
						Dst->SetPos(-fX, Dst->GetINFO().fY);
					}
					// 우 충돌
					else
					{
						Dst->SetPos(fX, Dst->GetINFO().fY);
					}
				}
			}
		}
	}
}

void CCollisionManager::CollisionRectEx2(list<CObject*> _Dst, list<CObject*> _Src)
{
	float	fX(0.f), fY(0.f);

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (CheckRect(Dst, Src, &fX, &fY))
			{
				if (Dst->GetOBJID() == OBJ_PLAYER && Src->GetOBJID() == OBJ_ITEM)
				{
					Dst->OnCollision(Src);
					Src->OnCollision(Dst);
				}
				// 좌 우 충돌
				if (fX < fY)
				{
					// 좌 충돌
					if (Dst->GetINFO().fX < Src->GetINFO().fX)
					{
						Dst->SetPos(Dst->GetINFO().fX - fX - Dst->GetSpeed(), Dst->GetINFO().fY);
						if (Dst->GetOBJID() == OBJ_ITEM && Src->GetOBJID() == OBJ_BLOCK) {
							Dst->OnCollision(Src);
						}
						if (Dst->GetOBJID() == OBJ_PLAYER && Src->GetOBJID() == OBJ_MONSTER) {
							Dst->OnCollision(Src);
						}
					}
					// 우 충돌
					else
					{
						Dst->SetPos(Dst->GetINFO().fX + fX + Dst->GetSpeed(), Dst->GetINFO().fY);
						if (Dst->GetOBJID() == OBJ_ITEM && Src->GetOBJID() == OBJ_BLOCK) {
							Dst->OnCollision(Src);
						}
						if (Dst->GetOBJID() == OBJ_PLAYER && Src->GetOBJID() == OBJ_MONSTER) {
							Dst->OnCollision(Src);
						}
					}
				}
				// 상 하 충돌
				else if (fX > fY)
				{
					// 상 충돌
					if (Dst->GetINFO().fY < Src->GetINFO().fY)
					{
						Dst->SetPos(Dst->GetINFO().fX, Dst->GetINFO().fY - fY - Dst->GetSpeed());
						Dst->SetIsGround(true);
						if (Dst->GetOBJID() == OBJ_PLAYER && Src->GetOBJID() == OBJ_MONSTER) {
							Src->OnCollision(Dst);
						}
					}
					// 하 충돌
					else
					{
						if (Src->GetOBJID() == OBJ_BLOCK)
						{
							Src->OnCollision(Dst);
						}
						Dst->SetPos(Dst->GetINFO().fX, Dst->GetINFO().fY + fY + Dst->GetSpeed());
						Dst->SetIsGround(false);
						if (Dst->GetOBJID() == OBJ_PLAYER && Src->GetOBJID() == OBJ_MONSTER) {
							Dst->OnCollision(Src);
						}
					}
				}
			}
		}
	}
}

bool CCollisionManager::CheckRect(CObject* _Dst, CObject* _Src, float* pX, float* pY)
{
	float		fX = abs(_Dst->GetINFO().fX - _Src->GetINFO().fX);
	float		fY = abs(_Dst->GetINFO().fY - _Src->GetINFO().fY);

	float		fRadiusX = (_Dst->GetINFO().fCX + _Src->GetINFO().fCX) * 0.5f;
	float		fRadiusY = (_Dst->GetINFO().fCY + _Src->GetINFO().fCY) * 0.5f;

	if ((fRadiusX >= fX) && (fRadiusY >= fY))
	{
		*pX = fRadiusX - fX;
		*pY = fRadiusY - fY;
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionLine(float _fX, float* pY)
{
	if (CLineManager::GetInstance()->GetList()[LINE_NONE].empty()) return false;

	CLine* pTargetLine = nullptr;
	CLine* closestLine = nullptr;
	float distance = FLT_MAX;

	for (auto& pLine : CLineManager::GetInstance()->GetList()[LINE_NONE])
	{
		float jumpY = CObjectManager::GetInstance()->GetPlayer()->GetINFO().fY;
		float x1 = pLine->GetLPoint().GetX();
		float y1 = pLine->GetLPoint().GetY();
		float x2 = pLine->GetRPoint().GetX();
		float y2 = pLine->GetRPoint().GetY();

		float cY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;
		distance = cY - jumpY;
		//jumpY
		if (_fX >= pLine->GetLPoint().GetX() && _fX < pLine->GetRPoint().GetX())
		{
			if (distance >= 0)
			{
				closestLine = pLine;
			}
			if (closestLine)
			{
				pTargetLine = closestLine;
			}
			else
			{
				pTargetLine = pLine;
			}
		}
	}

	if (!pTargetLine)
		return false;

	float x1 = pTargetLine->GetLPoint().GetX();
	float y1 = pTargetLine->GetLPoint().GetY();
	float x2 = pTargetLine->GetRPoint().GetX();
	float y2 = pTargetLine->GetRPoint().GetY();

	*pY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;
	return true;

	return false;
}

bool CCollisionManager::CheckRect(RECT& r1, RECT& r2)
{
	return !(r1.right <= r2.left || r1.left >= r2.right || r1.bottom <= r2.top || r1.top >= r2.bottom);
}

bool CCollisionManager::CheckRect(CObject* _Dst, CObject* _Src)
{
	RECT r1 = *_Dst->GetRECT();
	RECT r2 = *_Src->GetRECT();
	return !(r1.right <= r2.left || r1.left >= r2.right || r1.bottom <= r2.top || r1.top >= r2.bottom);
}

bool CCollisionManager::CollisionLine(INFO _tInfo, float* pY)
{

	if (CLineManager::GetInstance()->GetList()->empty())
		return false;

	CLine* pTargetLine = nullptr;
	list<CLine*> TargetLineList;

	for (auto& pLine : *CLineManager::GetInstance()->GetList())
	{
		if (_tInfo.fX >= pLine->GetLPoint().GetX() &&
			_tInfo.fX < pLine->GetRPoint().GetX())
		{
			//pTargetLine = pLine;
			TargetLineList.push_back(pLine);
		}
	}

	float fHeight(0.f);

	for (auto iter : TargetLineList)
	{
		if (iter->GetLPoint().GetY() < _tInfo.fY && iter->GetLPoint().GetY() < _tInfo.fY)
		{
			continue;
		}
		if (pTargetLine == nullptr || fHeight > iter->GetLPoint().GetY())
		{
			pTargetLine = iter;
			fHeight = iter->GetLPoint().GetY();
		}
	}

	if (nullptr == pTargetLine)
		return false;

	float x1 = pTargetLine->GetLPoint().GetX();
	float y1 = pTargetLine->GetLPoint().GetY();
	float x2 = pTargetLine->GetRPoint().GetX();
	float y2 = pTargetLine->GetRPoint().GetY();

	*pY = ((y2 - y1) / (x2 - x1)) * (_tInfo.fX - x1) + y1;

	return true;

}
