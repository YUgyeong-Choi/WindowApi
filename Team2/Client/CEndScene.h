#pragma once
#include "CSceneObject.h"
class CEndScene :public CSceneObject
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render(HDC hDC);
};

