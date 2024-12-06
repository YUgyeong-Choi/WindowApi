#pragma once

#include "CObject.h"

template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory() {}
	~CAbstractFactory() {};

public:
	static CObject* Create()
	{
		CObject* pObject = new T;
		pObject->Initialize();
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
};

