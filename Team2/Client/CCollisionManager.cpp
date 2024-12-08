#include "pch.h"
#include "../Client/CCollisionManager.h"
#include "../Client/CLineManager.h"
#include "../Client/CObjectManager.h"
#include "CBoss.h"
#include "CMHPlayer.h"

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
				if (Dst->GetID() == OBJ_PLAYER && Src->GetID() == OBJ_ITEM)
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
						Dst->SetPos(Dst->GetINFO().fX - fX - 10.f, Dst->GetINFO().fY);
					}
					// 우 충돌
					else
					{
 						Dst->SetPos(Dst->GetINFO().fX + fX + 10.f, Dst->GetINFO().fY);
					}
				}
				// 상 하 충돌
				else if (fX > fY)
				{
					// 상 충돌
					if (Dst->GetINFO().fY < Src->GetINFO().fY)
					{
						Dst->SetPos(Dst->GetINFO().fX, Dst->GetINFO().fY - fY - 10.f);
                        Dst->SetIsGround(true);
					}
					// 하 충돌
					else
					{
						if (Src->GetID() == OBJ_BOX)
						{
							Src->OnCollision(Dst);
						}
						Dst->SetPos(Dst->GetINFO().fX, Dst->GetINFO().fY + fY + 10.f);
						Dst->SetIsGround(false);
	      			}
				}
			}
		}
	}
}

void CCollisionManager::CollisionRectExDown(list<CObject*> _Dst, list<CObject*> _Src)
{
	float	fX(0.f), fY(0.f);

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (CheckBox3(Dst, Src, &fX, &fY))
			{
				Dst->SetPos((float)Src->GetRECT()->right, (float)Dst->GetINFO().fY);
			}
			else if (CheckBox4(Dst, Src, &fX, &fY))
			{
				Dst->SetPos((float)Src->GetRECT()->left, (float)Dst->GetINFO().fY);
			}
			else if (CheckBox2(Dst, Src, &fX, &fY))
			{
				Dst->SetIsJumping(false);
			}
			else if (CheckBox(Dst, Src, &fX, &fY))
			{
				Dst->OnCollision(Src);
				Src->OnCollision(Dst);
			}
			
		}
	}
}

bool CCollisionManager::CheckRect(RECT& r1, RECT& r2)
{
	return !(r1.right <= r2.left || r1.left >= r2.right || r1.bottom <= r2.top || r1.top >= r2.bottom);
}

void CCollisionManager::CollisionTestRect(list<CObject*> _Dst, list<CObject*> _Src)
{
	for (auto& Dst : _Dst)
	{
		/*RECT nextPlayer = *Dst->GetRECT();
		nextPlayer.left += 10;
		nextPlayer.right -= 10;
		nextPlayer.top -= 2;
		nextPlayer.bottom -= 2;*/
		for (auto& Src : _Src)
		{
			if (CheckRect(*Dst->GetRECT(), *Src->GetRECT()))
			{
				Dst->OnCollision(Src);
				Src->OnCollision(Dst);
			}
		}
	}
}

bool CCollisionManager::CheckRect(CObject* _Dst, CObject* _Src)
{
	RECT r1 = *_Dst->GetRECT();
	RECT r2 = *_Src->GetRECT();
	return !(r1.right <= r2.left || r1.left >= r2.right || r1.bottom <= r2.top || r1.top >= r2.bottom);
}

bool CCollisionManager::CheckBox(CObject* _Dst, CObject* _Src, float* pX, float* pY)
{
	RECT pBox = { (*_Dst->GetRECT()).left, (*_Dst->GetRECT()).bottom - 15, (*_Dst->GetRECT()).right, (*_Dst->GetRECT()).bottom };
	RECT bBox = { (*_Src->GetRECT()).left, (*_Src->GetRECT()).top, (*_Src->GetRECT()).right, (*_Src->GetRECT()).top + 15 };
	RECT intersection;
	return IntersectRect(&intersection, &pBox, &bBox);
}

bool CCollisionManager::CheckBox2(CObject* _Dst, CObject* _Src, float* pX, float* pY)
{
	RECT pBox = { (*_Dst->GetRECT()).left, (*_Dst->GetRECT()).top, (*_Dst->GetRECT()).right, (*_Dst->GetRECT()).top + 5 };
	RECT bBox = { (*_Src->GetRECT()).left, (*_Src->GetRECT()).bottom - 5, (*_Src->GetRECT()).right, (*_Src->GetRECT()).bottom };
	RECT intersection;
	return IntersectRect(&intersection, &pBox, &bBox);
}

//Player의 Left와 박스의 RIght가 충돌
bool CCollisionManager::CheckBox3(CObject* _Dst, CObject* _Src, float* pX, float* pY)
{
	RECT pBox = { (*_Dst->GetRECT()).left, (*_Dst->GetRECT()).top + 2, (*_Dst->GetRECT()).left + 5, (*_Dst->GetRECT()).bottom - 2 };
	RECT bBox = { (*_Src->GetRECT()).right - 5, (*_Src->GetRECT()).bottom + 2, (*_Src->GetRECT()).right, (*_Src->GetRECT()).bottom - 2 };
	RECT intersection;
	return IntersectRect(&intersection, &pBox, &bBox);
}

//Player의 Right와 박스의 left가 충돌
bool CCollisionManager::CheckBox4(CObject* _Dst, CObject* _Src, float* pX, float* pY)
{
	RECT pBox = { (*_Dst->GetRECT()).right - 5, (*_Dst->GetRECT()).top + 2, (*_Dst->GetRECT()).right, (*_Dst->GetRECT()).bottom -2 };
	RECT bBox = { (*_Src->GetRECT()).left, (*_Src->GetRECT()).top + 2, (*_Src->GetRECT()).left + 5, (*_Src->GetRECT()).bottom - 2 };
	RECT intersection;
	return IntersectRect(&intersection, &pBox, &bBox);
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

		//jumpY = currentY;
		if (_fX >= pLine->GetLPoint().GetX() && _fX < pLine->GetRPoint().GetX())
		{
			if (distance == 0)
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

void CCollisionManager::CollisionLine(CObject* player, list<CLine*> _l)
{
	for (auto& l : _l)
	{
		if (l->GetInfo()->tLPoint.fX > (player->GetINFO().fX - player->GetINFO().fCX * 0.5f))
		{
			player->SetPos(player->GetINFO().fX + player->GetINFO().fCX * 0.8f, player->GetINFO().fY);
		}
	}
}

void CCollisionManager::CollisionLine(list<CObject*> _Dst, list<CLine*> _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (CheckLine(Dst, Src))
			{
				Dst->SetTargetLine(Src);
			}
		}
	}
}

CLine* CCollisionManager::CollisionLine2(float _fX, float* pY)
{
	if (CLineManager::GetInstance()->GetList()[LINE_NONE].empty()) return nullptr;

	CLine* pTargetLine = nullptr;
	CLine* closestLine = nullptr;
	float minDistance = FLT_MAX;

	//만약에 조건에 해당하는 라인이 2개이상이면
	//jumpY 보다 아래있고 가장 가까운 것을 선택

	for (auto& pLine : CLineManager::GetInstance()->GetList()[LINE_NONE])
	{
		if (_fX >= pLine->GetLPoint().GetX() && _fX < pLine->GetRPoint().GetX())
		{
			float jumpY = CObjectManager::GetInstance()->GetPlayer()->GetINFO().fY;
			float x1 = pLine->GetLPoint().GetX();
			float y1 = pLine->GetLPoint().GetY();
			float x2 = pLine->GetRPoint().GetX();
			float y2 = pLine->GetRPoint().GetY();
			float cY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;
			if (cY >= jumpY - 20.f)
			{
				float distance = cY - jumpY;
				if (distance < minDistance)
				{
					minDistance = distance;
					closestLine = pLine;
					pTargetLine = closestLine;
				}
			}

		}	
	}

	if (!pTargetLine)
		return nullptr;

	float x1 = pTargetLine->GetLPoint().GetX();
	float y1 = pTargetLine->GetLPoint().GetY();
	float x2 = pTargetLine->GetRPoint().GetX();
	float y2 = pTargetLine->GetRPoint().GetY();

	*pY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;

	return closestLine;
}

bool CCollisionManager::CheckLine(CObject* _Dst, CLine* _src)
{

	float _fX = _Dst->GetINFO().fX;
	float cY = _src->GetCurrentY(_fX);
	if ((_fX >= _src->GetLPoint().GetX()) && (_fX <= _src->GetRPoint().GetX()))
	{
		float distance = cY - _Dst->GetRECT()->bottom;

		if (abs(distance) <= 20.f)
		{
			return true;
		}
			
	}
	return false;
}

bool CCollisionManager::CollisionBox(float _fX, float* pY)
{
    return false;
}

bool CCollisionManager::DetectPlayer(CObject* monster, CObject* player)
{
	if (player)
	{
		float fWidth = abs(monster->GetINFO().fX - player->GetINFO().fX);
		float fHeight = abs(monster->GetINFO().fY - player->GetINFO().fY);
		float fDiagonal = powf((fWidth * fWidth + fHeight * fHeight), 0.5f);
		if (dynamic_cast<CBoss*>(monster)->m_fDistance < fDiagonal) return true;
	}
	return false;
}
