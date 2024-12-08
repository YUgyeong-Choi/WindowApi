#pragma once

#include "CObject.h"
#include "CBox.h"
#include "CItem.h"
#include "CProjectile.h"

template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory() {}
	~CAbstractFactory() {};

public:
	static T* Create()
	{
		T* pObject = new T;
		pObject->Initialize();
		return pObject;
	}

	static CObject* Create(float _fX, float _fY, BOXTYPE _bt, float _fAngle = 0)
	{
		CObject* pObject = new T;
		pObject->Initialize();
		pObject->SetPos(_fX, _fY);
		pObject->SetAngle(_fAngle);
		if (pObject->GetID() == OBJ_BOX)
		{
			dynamic_cast<CBox*>(pObject)->SetBoxType(_bt);
		}

		return pObject;
	}

	static CObject* Create(float _fX, float _fY, Vector<float> _size, ITEMTYPE _it, float _fAngle = 0)
	{
		CObject* pObject = new T;
		pObject->Initialize();
		pObject->SetPos(_fX, _fY);
		pObject->SetSize(_size.GetX(), _size.GetY());
		pObject->SetAngle(_fAngle);
		if (pObject->GetID() == OBJ_ITEM)
		{
			dynamic_cast<CItem*>(pObject)->SetItemType(_it);
		}

		return pObject;
	}


	static CObject* Create(float _fX, float _fY, float _fAngle = 0)
	{
		CObject* pObject = new T;
		pObject->Initialize();
		pObject->SetPos(_fX, _fY);
		pObject->SetAngle(_fAngle);

		return pObject;
	}

	static CObject* Create(float _fX, float _fY, OBJID owner, float _fAngle = 0)
	{
		CObject* pObject = new T;
		pObject->Initialize();
		pObject->SetPos(_fX, _fY);
		pObject->SetAngle(_fAngle);
		if (pObject->GetID() == OBJ_PROJECTILE)
		{
			dynamic_cast<CProjectile*>(pObject)->m_eOwner = owner;
		}
		
		return pObject;
	}

	static CObject* Create(float _fX, float _fY, ITEMTYPE it, float _fAngle = 0)
	{
		CObject* pObject = new T;
		pObject->Initialize();
		pObject->SetPos(_fX, _fY);
		pObject->SetAngle(_fAngle);
		if (pObject->GetID() == OBJ_ITEM)
		{
			dynamic_cast<CItem*>(pObject)->SetItemType(it);
		}

		return pObject;
	}

	static CObject* Create(float _fX, float _fY,  Vector<float> _size, float _fAngle = 0)
	{
		CObject* pObject = new T;
		pObject->Initialize();
		pObject->SetPos(_fX, _fY);
		pObject->SetSize(_size.GetX(), _size.GetY());
		pObject->SetAngle(_fAngle);

		return pObject;
	}
};

